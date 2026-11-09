"""Integration checks for release-file integrity, not game behavior tests."""
from pathlib import Path
import hashlib,shutil,subprocess,sys,tempfile,zipfile
ROOT=Path(__file__).resolve().parents[1]

def verify(folder,success):
    result=subprocess.run([sys.executable,'-X','utf8',str(ROOT/'tools/verify_artifacts.py'),
        '--dir',str(folder),'--require-validated'],capture_output=True,text=True,encoding='utf8')
    if (result.returncode==0)!=success:raise AssertionError(result.stdout+result.stderr)

def main():
    with tempfile.TemporaryDirectory(prefix='sango-release-') as name:
        copy=Path(name)/'dist';shutil.copytree(ROOT/'dist',copy);verify(copy,True)
        bda=next(copy.glob('*.bda'));data=bytearray(bda.read_bytes());data[-5]^=1;bda.write_bytes(data)
        verify(copy,False)
        shutil.copy2(ROOT/'dist'/bda.name,bda)
        library=copy/'sango.lib';data=bytearray(library.read_bytes());data[-1]^=1;library.write_bytes(data)
        verify(copy,False)
        shutil.copy2(ROOT/'dist/sango.lib',library)
        color=copy/'sango.clr';data=bytearray(color.read_bytes());data[-1]^=1;color.write_bytes(data)
        verify(copy,False);shutil.copy2(ROOT/'dist/sango.clr',color)
        archive=next(copy.glob('*-update.zip'));original=archive.read_bytes()
        def rewrite_music(remove=False):
            with zipfile.ZipFile(ROOT/'dist'/archive.name) as z:
                contents={n:z.read(n) for n in z.namelist()}
            path='应用/数据/游戏/sango-music/battle.wav'
            if remove:del contents[path]
            else:
                audio=bytearray(contents[path]);audio[-1]^=1;contents[path]=bytes(audio)
            with zipfile.ZipFile(archive,'w',zipfile.ZIP_DEFLATED) as z:
                for name,data in contents.items():z.writestr(name,data)
            # Update outer digest so this exercises the installation verifier.
            sums=copy/'SHA256SUMS.txt'
            lines=sums.read_text(encoding='utf8').splitlines()
            sums.write_text('\n'.join(hashlib.sha256(archive.read_bytes()).hexdigest()+'  '+archive.name if line.endswith('  '+archive.name) else line for line in lines)+'\n',encoding='utf8')
        rewrite_music(remove=True);verify(copy,False)
        rewrite_music();verify(copy,False)
        archive.write_bytes(original);shutil.copy2(ROOT/'dist/SHA256SUMS.txt',copy/'SHA256SUMS.txt');verify(copy,True)
        (copy/'unexpected.sav').write_bytes(b'not-for-release')
        verify(copy,False)
    result=subprocess.run([sys.executable,'-X','utf8',str(ROOT/'tools/package_release.py'),'--tag','invalid-tag'],capture_output=True,text=True,encoding='utf8')
    if result.returncode==0:raise AssertionError('Invalid tag accepted')
    print('Release integration checks passed: valid assets, corruption, missing/tampered music, extra files and invalid tag.')

if __name__=='__main__':main()
