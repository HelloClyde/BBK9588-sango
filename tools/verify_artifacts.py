"""Verify downloaded/released files, not an Actions transport archive digest."""
from pathlib import Path
import argparse,hashlib,json,zipfile
ROOT=Path(__file__).resolve().parents[1]
def main():
    p=argparse.ArgumentParser();p.add_argument('--dir',type=Path,default=ROOT/'dist');p.add_argument('--require-validated',action='store_true');args=p.parse_args()
    files=[]
    for line in (args.dir/'SHA256SUMS.txt').read_text(encoding='utf-8').splitlines():
        digest,name=line.split('  ',1)
        if Path(name).name!=name:raise SystemExit('Invalid artifact path')
        data=(args.dir/name).read_bytes()
        if hashlib.sha256(data).hexdigest()!=digest:raise SystemExit('Artifact SHA-256 mismatch: '+name)
        files.append(name)
    info=json.loads((args.dir/'BUILD_INFO.json').read_text(encoding='utf-8'))
    if args.require_validated and not info['matches_runtime_reference']:raise SystemExit('Artifact lacks matching runtime evidence')
    prefix='BBK9588-sango-'+info['version'];bda=(args.dir/(prefix+'.bda')).read_bytes()
    with zipfile.ZipFile(args.dir/(prefix+'-update.zip')) as z:
        if z.testzip() is not None:raise SystemExit('Corrupt installation ZIP')
        expected={'应用/程序/三国霸业.bda','README.txt','LICENSE.md','LICENSES/MIT.txt',
            'LICENSES/SDK-Apache-2.0.txt','SDK-NOTICE.txt','THIRD_PARTY_NOTICES.md','SHA256SUMS.txt'}
        if set(z.namelist())!=expected or len(z.namelist())!=len(expected):raise SystemExit('Unexpected installation ZIP contents')
        if z.read('应用/程序/三国霸业.bda')!=bda:raise SystemExit('Installed BDA differs from released BDA')
    print(json.dumps({'passed':True,'verified_files':files,'resource_included':False,'runtime_reference_matches':info['matches_runtime_reference']},ensure_ascii=False))
if __name__=='__main__':main()
