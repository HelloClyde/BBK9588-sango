"""Package the built BDA, indexed LIB and RGB565 companion deterministically."""
from pathlib import Path
import argparse,hashlib,json,re,subprocess,zipfile

ROOT=Path(__file__).resolve().parents[1]
def sha(data):return hashlib.sha256(data).hexdigest()
def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--tag');p.add_argument('--require-validated',action='store_true');args=p.parse_args()
    version=(ROOT/'VERSION').read_text().strip()
    if not re.fullmatch(r'\d+\.\d+\.\d+(?:-[a-z0-9]+(?:\.\d+)?)?',version):raise SystemExit('Invalid VERSION')
    if args.tag and args.tag!='v'+version:raise SystemExit('Tag does not match VERSION')
    built=json.loads((ROOT/'build/build-result.json').read_text(encoding='utf-8'))
    reference=json.loads((ROOT/'validation/reference-build.json').read_text(encoding='utf-8'))
    bda=(ROOT/'build/三国霸业.bda').read_bytes()
    library=(ROOT/'build/sango.lib').read_bytes()
    color=(ROOT/'build/sango.clr').read_bytes()
    if sha(bda)!=built['sha256']:raise SystemExit('BDA differs from successful build metadata')
    if sha(library)!=built['library_sha256']:raise SystemExit('Library differs from successful build metadata')
    if sha(color)!=built['color_sha256']:raise SystemExit('Color companion differs from build metadata')
    verified=sha(bda)==reference['bda_sha256']
    library_verified=sha(library)==reference.get('sango_lib_sha256')
    color_verified=sha(color)==reference.get('sango_clr_sha256')
    if (args.require_validated or args.tag) and not verified:raise SystemExit('No matching runtime validation evidence for this BDA')
    if (args.require_validated or args.tag) and not library_verified:raise SystemExit('Library differs from resource validation reference')
    if (args.require_validated or args.tag) and not color_verified:raise SystemExit('Color companion differs from runtime validation reference')
    dist=ROOT/'dist';dist.mkdir(exist_ok=True)
    name=f'BBK9588-sango-{version}';(dist/(name+'.bda')).write_bytes(bda)
    (dist/'sango.lib').write_bytes(library)
    (dist/'sango.clr').write_bytes(color)
    instructions='''三国霸业 9588 C 重建：程序与资源包\n\n将“应用”目录合并到9588内置存储根目录：\n应用/程序/三国霸业.bda\n应用/数据/游戏/sango.lib\n应用/数据/游戏/sango.clr\n\n三份文件请一起安装。sango.lib 保留原索引、遮罩和动画；sango.clr 提供全部1204帧彩色素材。\n升级前备份设备同名程序和资源。存档路径不在包内，不覆盖个人存档。\n安全弹出设备并退出USB模式后，从娱乐天地启动。\n方向键选择/移动，确定执行，返回取消。也可直接触摸菜单、城池、武将、目的地和操作选项，按住地图拖动移动视野。松手不会确认城池、人物或命令；轻点空地只移动光标。
点击底部君主头像进入原返回键菜单；数值面板有减少/增加/确定/返回。信息页以16像素字体整页显示，点击或按键返回。问号、天气和河流轮廓素材位于sango.clr，请连同程序一起更新。\n不要把源码压缩包整体复制到设备。\n\n这是预发布版本，真机和完整战役尚未系统验证。\n本版已进行资源完整性、编译MIPS和彩色固件界面验证；固件检查以受控RAM资源装载隔离合成NAND的ECC差异。\n原作和素材许可范围见随包声明，SDK许可不代表原作许可。\n'''
    sums=sha(bda)+'  应用/程序/三国霸业.bda\n'+sha(library)+'  应用/数据/游戏/sango.lib\n'+sha(color)+'  应用/数据/游戏/sango.clr\n'
    contents={'应用/程序/三国霸业.bda':bda,'应用/数据/游戏/sango.lib':library,'应用/数据/游戏/sango.clr':color,'README.txt':instructions.encode('utf-8'),
        'LICENSE.md':(ROOT/'LICENSE.md').read_bytes(),'LICENSES/MIT.txt':(ROOT/'LICENSES/MIT.txt').read_bytes(),
        'LICENSES/SDK-Apache-2.0.txt':(ROOT/'sdk/LICENSE').read_bytes(),'SDK-NOTICE.txt':(ROOT/'sdk/NOTICE').read_bytes(),
        'THIRD_PARTY_NOTICES.md':(ROOT/'THIRD_PARTY_NOTICES.md').read_bytes(),
        'SHA256SUMS.txt':sums.encode('utf-8')}
    with zipfile.ZipFile(dist/(name+'-update.zip'),'w',zipfile.ZIP_DEFLATED,compresslevel=9) as z:
        for n,data in contents.items():
            item=zipfile.ZipInfo(n,(1980,1,1,0,0,0));item.compress_type=zipfile.ZIP_DEFLATED;item.external_attr=0o100644<<16;z.writestr(item,data)
    commit=subprocess.run(['git','-C',str(ROOT),'rev-parse','HEAD'],capture_output=True,text=True)
    info={'version':version,'source_commit':commit.stdout.strip() if commit.returncode==0 else None,
        **built,'matches_runtime_reference':verified,'matches_library_reference':library_verified,'matches_color_reference':color_verified,
        'runtime_evidence':{'mips_checks':reference['mips_checks'],'native_firmware_interface_checks':reference['native_firmware_interface_checks']} if verified else None,
        'ci_scope':'Build, SDK static validation, compiled MIPS color/HUD/summary/viewport/touch/info-weather/river-geometry/battle-options checks and packaging; no firmware emulator is run by Actions.',
        'resource_included':True,'color_included':True,'original_resource_sha256':reference['original_sango_lib_sha256'],
        'library_validation_scope':'Host lossless LIB rebuild and all 1204 native PNG/RGB565 frames checked; real compiled-MIPS loader/CRC/index/raster checks; native C200 RGB SDK rendering with exact expanded LIB/CLR staged in controlled RAM. No native filesystem or full-campaign claim.'}
    (dist/'BUILD_INFO.json').write_text(json.dumps(info,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
    files=[dist/(name+'.bda'),dist/'sango.lib',dist/'sango.clr',dist/(name+'-update.zip'),dist/'BUILD_INFO.json']
    (dist/'SHA256SUMS.txt').write_text(''.join(sha(f.read_bytes())+'  '+f.name+'\n' for f in files),encoding='utf-8')
    print(json.dumps({'version':version,'bda_sha256':sha(bda),'runtime_reference_matches':verified,'assets':[f.name for f in files]},ensure_ascii=False))

if __name__=='__main__':main()
