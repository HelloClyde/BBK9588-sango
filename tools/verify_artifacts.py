"""Verify downloaded/released files, not an Actions transport archive digest."""
from pathlib import Path
import argparse,hashlib,json,zipfile,struct,zlib
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
    if args.require_validated and not info['matches_library_reference']:raise SystemExit('Library lacks matching resource validation')
    if args.require_validated and not info['matches_color_reference']:raise SystemExit('Color lacks matching runtime validation')
    if args.require_validated and not info.get('matches_music_reference'):raise SystemExit('Music lacks matching audio validation')
    if [t['id'] for t in info.get('music',[])]!=['menu','strategy','battle']:raise SystemExit('Missing music scenes')
    prefix='BBK9588-sango-'+info['version'];bda=(args.dir/(prefix+'.bda')).read_bytes()
    library=(args.dir/'sango.lib').read_bytes()
    color=(args.dir/'sango.clr').read_bytes()
    magic,total,count,index,payload,size,crc=struct.unpack_from('<8sIIIIII',color)
    if (magic,total,count,index,payload,size,crc)!=(b'SGCOLOR1',len(color),info['color_frames'],32,32+info['color_frames']*16,len(library),zlib.crc32(library)):raise SystemExit('Invalid color header or wrong companion LIB')
    expected_files={prefix+'.bda','sango.lib','sango.clr',prefix+'-update.zip','BUILD_INFO.json','SHA256SUMS.txt'}
    if {p.name for p in args.dir.iterdir()}!=expected_files:raise SystemExit('Unexpected files in release directory')
    if set(files)!=expected_files-{'SHA256SUMS.txt'} or len(files)!=5:raise SystemExit('Incomplete checksum manifest')
    digest=hashlib.sha256(bda).hexdigest()
    if digest!=info['sha256']:raise SystemExit('BDA differs from build metadata')
    if hashlib.sha256(library).hexdigest()!=info['library_sha256']:raise SystemExit('Library differs from build metadata')
    if hashlib.sha256(color).hexdigest()!=info['color_sha256']:raise SystemExit('Color companion differs from build metadata')
    if args.require_validated:
        reference=json.loads((ROOT/'validation/reference-build.json').read_text(encoding='utf-8'))
        if digest!=reference['bda_sha256'] or info['sdk_commit']!=reference['sdk_commit']:
            raise SystemExit('Release differs from runtime validation reference')
        if hashlib.sha256(library).hexdigest()!=reference['sango_lib_sha256']:
            raise SystemExit('Release differs from resource validation reference')
    if args.require_validated and hashlib.sha256(color).hexdigest()!=reference['sango_clr_sha256']:raise SystemExit('Release differs from color validation reference')
    if args.require_validated and info['music']!=reference.get('music_tracks'):raise SystemExit('Release music differs from audio reference')
    with zipfile.ZipFile(args.dir/(prefix+'-update.zip')) as z:
        if z.testzip() is not None:raise SystemExit('Corrupt installation ZIP')
        expected={'应用/程序/三国霸业.bda','应用/数据/游戏/sango.lib','应用/数据/游戏/sango.clr','README.txt','LICENSE.md','LICENSES/MIT.txt',
            'LICENSES/SDK-Apache-2.0.txt','SDK-NOTICE.txt','THIRD_PARTY_NOTICES.md','SHA256SUMS.txt'}
        expected.update('应用/数据/游戏/sango-music/'+t['file'] for t in info['music'])
        if set(z.namelist())!=expected or len(z.namelist())!=len(expected):raise SystemExit('Unexpected installation ZIP contents')
        if z.read('应用/程序/三国霸业.bda')!=bda:raise SystemExit('Installed BDA differs from released BDA')
        if z.read('应用/数据/游戏/sango.lib')!=library:raise SystemExit('Installed library differs from released library')
        if z.read('应用/数据/游戏/sango.clr')!=color:raise SystemExit('Installed color differs from released color')
        expected_sums=digest+'  应用/程序/三国霸业.bda\n'+hashlib.sha256(library).hexdigest()+'  应用/数据/游戏/sango.lib\n'+hashlib.sha256(color).hexdigest()+'  应用/数据/游戏/sango.clr\n'
        for track in info['music']:
            if track['file']!=track['id']+'.wav':raise SystemExit('Invalid music filename')
            path='应用/数据/游戏/sango-music/'+track['file'];data=z.read(path)
            if len(data)!=track['bytes'] or hashlib.sha256(data).hexdigest()!=track['sha256']:raise SystemExit('Music checksum mismatch: '+path)
            # Keep verification usable standalone in the Linux release job.
            if data[:4]!=b'RIFF' or data[8:12]!=b'WAVE' or struct.unpack_from('<I',data,4)[0]+8!=len(data):raise SystemExit('Invalid music WAV')
            expected_sums+=track['sha256']+'  '+path+'\n'
        if z.read('SHA256SUMS.txt')!=expected_sums.encode('utf-8'):raise SystemExit('Installation checksum manifest mismatch')
    print(json.dumps({'passed':True,'verified_files':files,'resource_included':True,'runtime_reference_matches':info['matches_runtime_reference']},ensure_ascii=False))
if __name__=='__main__':main()
