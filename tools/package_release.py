"""Package the built BDA and regenerated sango.lib deterministically."""
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
    if sha(bda)!=built['sha256']:raise SystemExit('BDA differs from successful build metadata')
    if sha(library)!=built['library_sha256']:raise SystemExit('Library differs from successful build metadata')
    verified=sha(bda)==reference['bda_sha256']
    library_verified=sha(library)==reference.get('sango_lib_sha256')
    if (args.require_validated or args.tag) and not verified:raise SystemExit('No matching runtime validation evidence for this BDA')
    if (args.require_validated or args.tag) and not library_verified:raise SystemExit('Library differs from resource validation reference')
    dist=ROOT/'dist';dist.mkdir(exist_ok=True)
    name=f'BBK9588-sango-{version}';(dist/(name+'.bda')).write_bytes(bda)
    (dist/'sango.lib').write_bytes(library)
    instructions='''三国霸业 9588 C 重建：程序与资源包\n\n将“应用”目录合并到9588内置存储根目录：\n应用/程序/三国霸业.bda\n应用/数据/游戏/sango.lib\n\n本包附带从仓库素材重新打包的 sango.lib，包含全部原资源和补充底栏、制作群组。\n升级前备份设备同名程序和资源。存档路径不在包内，不覆盖个人存档。\n安全弹出设备并退出USB模式后，从娱乐天地启动。\n方向键选择/移动，确定执行，返回取消；触摸信息/查找。\n不要把源码压缩包整体复制到设备。\n\n这是预发布版本，真机完整战役、长按及全部触摸合成ESC路径尚未系统验证。\n本次新增资源包做了主机无损回包及兼容检查，原生模拟器证据对应同一BDA配原资源库。\n原作和素材许可范围见随包声明，SDK许可不代表原作许可。\n'''
    sums=sha(bda)+'  应用/程序/三国霸业.bda\n'+sha(library)+'  应用/数据/游戏/sango.lib\n'
    contents={'应用/程序/三国霸业.bda':bda,'应用/数据/游戏/sango.lib':library,'README.txt':instructions.encode('utf-8'),
        'LICENSE.md':(ROOT/'LICENSE.md').read_bytes(),'LICENSES/MIT.txt':(ROOT/'LICENSES/MIT.txt').read_bytes(),
        'LICENSES/SDK-Apache-2.0.txt':(ROOT/'sdk/LICENSE').read_bytes(),'SDK-NOTICE.txt':(ROOT/'sdk/NOTICE').read_bytes(),
        'THIRD_PARTY_NOTICES.md':(ROOT/'THIRD_PARTY_NOTICES.md').read_bytes(),
        'SHA256SUMS.txt':sums.encode('utf-8')}
    with zipfile.ZipFile(dist/(name+'-update.zip'),'w',zipfile.ZIP_DEFLATED,compresslevel=9) as z:
        for n,data in contents.items():
            item=zipfile.ZipInfo(n,(1980,1,1,0,0,0));item.compress_type=zipfile.ZIP_DEFLATED;item.external_attr=0o100644<<16;z.writestr(item,data)
    commit=subprocess.run(['git','-C',str(ROOT),'rev-parse','HEAD'],capture_output=True,text=True)
    info={'version':version,'source_commit':commit.stdout.strip() if commit.returncode==0 else None,
        **built,'matches_runtime_reference':verified,'matches_library_reference':library_verified,
        'runtime_evidence':{'mips_checks':reference['mips_checks'],'native_firmware_interface_checks':reference['native_firmware_interface_checks']} if verified else None,
        'ci_scope':'Build, SDK static validation and packaging; no firmware emulator is run by Actions.',
        'resource_included':True,'original_resource_sha256':reference['original_sango_lib_sha256'],
        'library_validation_scope':'Host lossless rebuild, preservation of all 87 original records and C supplemental pixel equivalence; native runtime evidence uses the original library.'}
    (dist/'BUILD_INFO.json').write_text(json.dumps(info,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
    files=[dist/(name+'.bda'),dist/'sango.lib',dist/(name+'-update.zip'),dist/'BUILD_INFO.json']
    (dist/'SHA256SUMS.txt').write_text(''.join(sha(f.read_bytes())+'  '+f.name+'\n' for f in files),encoding='utf-8')
    print(json.dumps({'version':version,'bda_sha256':sha(bda),'runtime_reference_matches':verified,'assets':[f.name for f in files]},ensure_ascii=False))

if __name__=='__main__':main()
