"""Create a deterministic BDA update package without original game dumps."""
from pathlib import Path
import argparse,hashlib,json,re,shutil,subprocess,zipfile

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
    if sha(bda)!=built['sha256']:raise SystemExit('BDA differs from successful build metadata')
    verified=sha(bda)==reference['bda_sha256']
    if (args.require_validated or args.tag) and not verified:raise SystemExit('No matching runtime validation evidence for this BDA')
    dist=ROOT/'dist';dist.mkdir(exist_ok=True)
    name=f'BBK9588-sango-{version}';(dist/(name+'.bda')).write_bytes(bda)
    instructions='''三国霸业 9588 C 重建：升级包\n\n将“应用”目录合并到9588内置存储根目录，程序目标为：\n应用/程序/三国霸业.bda\n\n保留设备已有的 应用/数据/游戏/sango.LIB。本包不附带原版资源。\n如设备尚无该资源，请从自己已有的原游戏安装中取得，不要把源码压缩包整体复制到设备。\n安全弹出设备并退出USB模式后，从娱乐天地启动。\n方向键选择/移动，确定执行，返回取消；触摸信息/查找。\n升级前自行保留同名程序备份；本包不覆盖资源和存档。\n\n这是预发布版本，真机完整战役、长按及全部触摸合成ESC路径尚未系统验证。\n原作和素材许可范围见随包声明，SDK许可不代表原作许可。\n'''
    contents={'应用/程序/三国霸业.bda':bda,'README.txt':instructions.encode('utf-8'),
        'LICENSE.md':(ROOT/'LICENSE.md').read_bytes(),'LICENSES/MIT.txt':(ROOT/'LICENSES/MIT.txt').read_bytes(),
        'LICENSES/SDK-Apache-2.0.txt':(ROOT/'sdk/LICENSE').read_bytes(),'SDK-NOTICE.txt':(ROOT/'sdk/NOTICE').read_bytes(),
        'THIRD_PARTY_NOTICES.md':(ROOT/'THIRD_PARTY_NOTICES.md').read_bytes(),
        'SHA256SUMS.txt':(sha(bda)+'  应用/程序/三国霸业.bda\n').encode('utf-8')}
    with zipfile.ZipFile(dist/(name+'-update.zip'),'w',zipfile.ZIP_DEFLATED,compresslevel=9) as z:
        for n,data in contents.items():
            item=zipfile.ZipInfo(n,(1980,1,1,0,0,0));item.compress_type=zipfile.ZIP_DEFLATED;item.external_attr=0o100644<<16;z.writestr(item,data)
    commit=subprocess.run(['git','-C',str(ROOT),'rev-parse','HEAD'],capture_output=True,text=True)
    info={'version':version,'source_commit':commit.stdout.strip() if commit.returncode==0 else None,
        **built,'matches_runtime_reference':verified,
        'runtime_evidence':{'mips_checks':reference['mips_checks'],'native_firmware_interface_checks':reference['native_firmware_interface_checks']} if verified else None,
        'ci_scope':'Build, SDK static validation and packaging; no firmware emulator is run by Actions.',
        'resource_included':False,'required_resource_sha256':reference['original_sango_lib_sha256']}
    (dist/'BUILD_INFO.json').write_text(json.dumps(info,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
    files=[dist/(name+'.bda'),dist/(name+'-update.zip'),dist/'BUILD_INFO.json']
    (dist/'SHA256SUMS.txt').write_text(''.join(sha(f.read_bytes())+'  '+f.name+'\n' for f in files),encoding='utf-8')
    print(json.dumps({'version':version,'bda_sha256':sha(bda),'runtime_reference_matches':verified,'assets':[f.name for f in files]},ensure_ascii=False))

if __name__=='__main__':main()
