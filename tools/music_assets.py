"""Validate bundled music, or convert the three user-supplied FLAC masters.

Normal builds need neither FFmpeg nor the original FLAC files.
"""
from pathlib import Path
import argparse,hashlib,json,struct,subprocess,tempfile,math

ROOT=Path(__file__).resolve().parents[1]
ASSETS=ROOT/'assets/music'
TRACKS=[('menu','谈笑风云_史诗主题V2','谈笑风云_史诗主题V2'),
        ('strategy','帷幄清风_策略谋划','帷幄清风_策略谋划'),
        ('battle','铁甲冲阵_器乐返修V7','铁甲冲阵_器乐返修V7')]


def sha(data):return hashlib.sha256(data).hexdigest()


def inspect_wave(data):
    if len(data)<60 or data[:4]!=b'RIFF' or data[8:12]!=b'WAVE' or struct.unpack_from('<I',data,4)[0]+8!=len(data):
        raise ValueError('Invalid music RIFF/WAVE length')
    offset=12;info={}
    while offset+8<=len(data):
        tag=data[offset:offset+4];size=struct.unpack_from('<I',data,offset+4)[0];start=offset+8
        if size>len(data)-start:raise ValueError('Truncated music chunk')
        if tag==b'fmt ':
            if 'format' in info or size<20:raise ValueError('Invalid music fmt')
            spec=struct.unpack_from('<HHIIHHHH',data,start)
            if spec[:3]!=(17,1,22050) or spec[4:]!=(256,4,2,505):raise ValueError('Expected mono22050 IMA ADPCM,256-byte/505-sample blocks')
            info['format']=list(spec)
        elif tag==b'fact':
            if 'samples' in info or size<4:raise ValueError('Invalid music fact')
            info['samples']=struct.unpack_from('<I',data,start)[0];info['fact_offset']=start
        elif tag==b'data':
            if 'data_offset' in info or not size or size%256:raise ValueError('Invalid music data')
            info['data_offset']=start;info['data_bytes']=size
        offset=start+size+(size&1)
    if offset!=len(data) or not all(k in info for k in ['format','samples','data_offset']):raise ValueError('Missing music chunks')
    maximum=info['data_bytes']//256*505
    if not maximum-505<info['samples']<=maximum:raise ValueError('Music sample count outside final block')
    for offset in range(info['data_offset'],info['data_offset']+info['data_bytes'],256):
        if data[offset+2]>88 or data[offset+3]!=0:raise ValueError('Invalid ADPCM block predictor/index')
    info['duration_seconds']=round(info['samples']/22050,6)
    return info


def validate():
    manifest=json.loads((ASSETS/'manifest.json').read_text(encoding='utf8'))
    if [t['id'] for t in manifest['tracks']]!=['menu','strategy','battle']:raise ValueError('Music scene order changed')
    result=[]
    for track in manifest['tracks']:
        path=ASSETS/track['path'];data=path.read_bytes();info=inspect_wave(data)
        if sha(data)!=track['sha256'] or len(data)!=track['bytes'] or info['samples']!=track['samples']:raise ValueError('Music differs from reviewed conversion: '+track['id'])
        result.append({'id':track['id'],'path':track['path'],'bytes':len(data),'sha256':sha(data),**info})
    return {'format':'IMA ADPCM WAV mono22050/4bit; runtime decodes to SDK22050/16/mono',
            'bytes':sum(t['bytes'] for t in result),'tracks':result}


def convert(source_dir):
    (ASSETS/'runtime').mkdir(parents=True,exist_ok=True);tracks=[]
    version=subprocess.check_output(['ffmpeg','-version'],text=True).splitlines()[0]
    with tempfile.TemporaryDirectory(prefix='sango-music-') as tmp:
        for ident,folder,title in TRACKS:
            source=source_dir/folder/(title+'.flac')
            probe=json.loads(subprocess.check_output(['ffprobe','-v','error','-show_entries','format=duration:stream=sample_rate,channels','-of','json',str(source)]))
            duration=float(probe['format']['duration']);pcm=Path(tmp)/(ident+'.pcm');dest=ASSETS/'runtime'/(ident+'.wav')
            # Full track, downmixed/resampled once.20ms endpoint fades avoid
            # clicks at a hard loop/scene boundary without trimming the song.
            filters=f'afade=t=in:d=0.02,afade=t=out:st={duration-.02:.6f}:d=0.02'
            subprocess.run(['ffmpeg','-hide_banner','-loglevel','error','-y','-i',str(source),'-map','0:a:0','-vn','-ac','1','-ar','22050','-af',filters,'-f','s16le',str(pcm)],check=True)
            reference=pcm.read_bytes();samples=len(reference)//2
            subprocess.run(['ffmpeg','-hide_banner','-loglevel','error','-y','-f','s16le','-ar','22050','-ac','1','-i',str(pcm),'-map_metadata','-1','-fflags','+bitexact','-flags:a','+bitexact','-c:a','adpcm_ima_wav','-block_size','256',str(dest)],check=True)
            data=bytearray(dest.read_bytes());info=inspect_wave(data)
            # FFmpeg5.1's WAV muxer counts padding samples. The final block
            # is retained, but fact exposes exactly the original resample.
            struct.pack_into('<I',data,info['fact_offset'],samples);dest.write_bytes(data);info=inspect_wave(data)
            decoded=subprocess.check_output(['ffmpeg','-hide_banner','-loglevel','error','-i',str(dest),'-f','s16le','-'])[:samples*2]
            if len(decoded)!=samples*2:raise ValueError('Decoded music truncated')
            from array import array
            left=array('h',reference);right=array('h',decoded)
            signal=sum(x*x for x in left);noise=sum((x-y)**2 for x,y in zip(left,right))
            snr=10*math.log10(signal/max(1,noise));peak=max(abs(x) for x in right)
            track={'id':ident,'title':title,'source_folder':folder,'source_file':title+'.flac',
                   'source_sha256':sha(source.read_bytes()),'source_bytes':source.stat().st_size,
                   'source_sample_rate':int(probe['streams'][0]['sample_rate']),'source_channels':probe['streams'][0]['channels'],
                   'path':'runtime/'+ident+'.wav','install_path':'应用/数据/游戏/sango-music/'+ident+'.wav',
                   'bytes':len(data),'sha256':sha(data),'samples':samples,'duration_seconds':info['duration_seconds'],
                   'resampled_pcm16_sha256':sha(reference),'ffmpeg_decoded_pcm16_sha256':sha(decoded),
                   'adpcm_snr_db':round(snr,3),'decoded_peak':peak}
            tracks.append(track);print(json.dumps({'id':ident,'bytes':len(data),'seconds':info['duration_seconds'],'snr_db':round(snr,2)},ensure_ascii=False),flush=True)
    manifest={'schema':1,'source':'Three full FLAC tracks supplied by the user; original masters retained at their source paths and not modified.',
              'converter':version,'sample_rate':22050,'channels':1,'storage_bits':4,'output_bits':16,
              'block_bytes':256,'samples_per_block':505,'endpoint_fade_seconds':.02,'tracks':tracks}
    (ASSETS/'manifest.json').write_text(json.dumps(manifest,ensure_ascii=False,indent=2)+'\n',encoding='utf8',newline='\n')
    print(json.dumps(validate(),ensure_ascii=False))


if __name__=='__main__':
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--source-dir',type=Path);a=p.parse_args()
    if a.source_dir:convert(a.source_dir)
    else:print(json.dumps(validate(),ensure_ascii=False))
