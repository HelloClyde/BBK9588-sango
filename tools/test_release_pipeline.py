"""Integration checks for release-file integrity, not game behavior tests."""
from pathlib import Path
import shutil,subprocess,sys,tempfile
ROOT=Path(__file__).resolve().parents[1]

def verify(folder,success):
    result=subprocess.run([sys.executable,str(ROOT/'tools/verify_artifacts.py'),
        '--dir',str(folder),'--require-validated'],capture_output=True,text=True)
    if (result.returncode==0)!=success:raise AssertionError(result.stdout+result.stderr)

def main():
    with tempfile.TemporaryDirectory(prefix='sango-release-') as name:
        copy=Path(name)/'dist';shutil.copytree(ROOT/'dist',copy);verify(copy,True)
        bda=next(copy.glob('*.bda'));data=bytearray(bda.read_bytes());data[-5]^=1;bda.write_bytes(data)
        verify(copy,False)
        shutil.copy2(ROOT/'dist'/bda.name,bda)
        library=copy/'sango.lib';data=bytearray(library.read_bytes());data[-1]^=1;library.write_bytes(data)
        verify(copy,False)
        shutil.copy2(ROOT/'dist/sango.lib',library);(copy/'unexpected.sav').write_bytes(b'not-for-release')
        verify(copy,False)
    result=subprocess.run([sys.executable,str(ROOT/'tools/package_release.py'),'--tag','invalid-tag'],capture_output=True,text=True)
    if result.returncode==0:raise AssertionError('Invalid tag accepted')
    print('Release integration checks passed: valid assets, corruption, extra files and invalid tag.')

if __name__=='__main__':main()
