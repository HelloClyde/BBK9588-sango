"""Cross-check bundled ADPCM against FFmpeg hashes and real MIPS streaming."""
from pathlib import Path
import hashlib,json,struct
from array import array
from music_assets import ROOT,ASSETS,inspect_wave,validate
from test_control_flow import Machine,STATE,BUFFER

STEPS=(7,8,9,10,11,12,13,14,16,17,19,21,23,25,28,31,34,37,41,45,50,55,60,66,73,80,88,97,107,118,130,143,157,173,190,209,230,253,279,307,337,371,408,449,494,544,598,658,724,796,876,963,1060,1166,1282,1411,1552,1707,1878,2066,2272,2499,2749,3024,3327,3660,4026,4428,4871,5358,5894,6484,7132,7845,8630,9493,10442,11487,12635,13899,15289,16818,18500,20350,22385,24623,27086,29794,32767)


def decode(block):
    predictor,index=struct.unpack_from('<hB',block);values=[predictor]
    assert index<=88 and block[3]==0
    for byte in block[4:]:
        for nibble in (byte&15,byte>>4):
            difference=STEPS[index]*(2*(nibble&7)+1)//8
            predictor=max(-32768,min(32767,predictor+(-difference if nibble&8 else difference)))
            index=max(0,min(88,index+(-1,-1,-1,-1,2,4,6,8)[nibble&7]))
            values.append(predictor)
    return struct.pack('<505h',*values)


def wave_fixture(source,samples=500):
    result=bytearray(source[:60]+source[60+256*100:60+256*101])
    struct.pack_into('<I',result,4,len(result)-8);struct.pack_into('<I',result,48,samples);struct.pack_into('<I',result,56,256)
    return bytes(result)


class Player:
    def __init__(self,files,frame=123):
        self.m=Machine((ROOT/'build/sango.elf').read_bytes());self.files=files;self.handles={};self.log=[];self.output=bytearray();self.clock=100;self.capacity=8;self.limit=1024;self.read_limit=4096;self.fail_seek=False;self.write_error=False;self.attenuate_in_place=False
        self.m.word(STATE['g_app_frame'],frame)
        if 'sango_music_sdk_diagnostic_start' in self.m.symbols:
            self.m.intercept('sango_music_sdk_diagnostic_start',1,lambda a:None)
        self.m.write(BUFFER,'A:\\应用\\数据\\游戏\\sango.lib'.encode('gbk')+b'\0')
        if 'sango_music_sdk_clock' in self.m.symbols:
            self.m.intercept('sango_music_sdk_clock',0,lambda a:self.clock)
        self.m.intercept('sango_music_sdk_timer',1,lambda a:self.log.append(('timer',a[0])))
        self.m.intercept('sango_music_sdk_audio_open',0,lambda a:self.log.append(('audio-open',)))
        self.m.intercept('sango_music_sdk_audio_stop',0,lambda a:self.log.append(('audio-stop',)))
        self.m.intercept('sango_music_sdk_audio_ready',0,lambda a:int(self.capacity>0))
        def open_file(a):
            name=self.m.text(a[0]).split(b'\\')[-1].decode('ascii');self.log.append(('open',name))
            if name not in self.files:return 0
            handle=len(self.log)+100;self.handles[handle]=[self.files[name],0];return handle
        def close_file(a):self.log.append(('close',a[0]));del self.handles[a[0]]
        def seek(a):
            if self.fail_seek:return -1
            data,pos=self.handles[a[0]];offset=a[1] if a[1]<0x80000000 else a[1]-0x100000000
            pos=(0 if a[2]==0 else len(data) if a[2]==2 else pos)+offset
            if pos<0 or pos>len(data):return -1
            self.handles[a[0]][1]=pos;return pos
        def read(a):
            data,pos=self.handles[a[0]];got=min(a[2],len(data)-pos,self.read_limit)
            self.m.write(a[1],data[pos:pos+got]);self.handles[a[0]][1]+=got;self.log.append(('read',got));return got
        def write(a):
            if self.write_error:return -1
            got=min(a[1],self.limit);data=self.m.read(a[0],got);self.output.extend(data)
            if self.attenuate_in_place:
                values=struct.unpack('<'+str(got//2)+'h',data);self.m.write(a[0],struct.pack('<'+str(len(values))+'h',*(v*9//16 for v in values)))
            self.capacity-=1;self.log.append(('write',got));return got
        for name,count,callback in [('file_open',1,open_file),('file_close',1,close_file),('file_read',3,read),('file_seek',3,seek),('audio_write',2,write)]:self.m.intercept('sango_music_sdk_'+name,count,callback)
        self.m.call('sango_music_set_library_path',BUFFER)
    def scene(self,n):self.m.call('sango_music_set_scene',n)
    def poll(self,capacity=8,elapsed=20):self.capacity=capacity;self.clock=(self.clock+elapsed)&0xffffffff;self.m.call('sango_music_poll')
    def stop(self):self.m.call('sango_music_shutdown')


def main():
    manifest=json.loads((ASSETS/'manifest.json').read_text(encoding='utf8'));validate();raw={};checks=0;host=[]
    codec=Machine((ROOT/'build/sango.elf').read_bytes())
    for track in manifest['tracks']:
        data=(ASSETS/track['path']).read_bytes();raw[track['id']+'.wav']=data;info=inspect_wave(data);remaining=info['samples'];digest=hashlib.sha256()
        offsets=list(range(info['data_offset'],len(data),256));chosen={0,1,2,10,100,len(offsets)//2,len(offsets)-2,len(offsets)-1}
        for number,offset in enumerate(offsets):
            pcm=decode(data[offset:offset+256]);take=min(remaining,505)*2;digest.update(pcm[:take]);remaining-=take//2
            if number in chosen:
                codec.write(BUFFER,data[offset:offset+256]);assert codec.call('sango_music_decode_ima_block',BUFFER,BUFFER+512)==505
                assert codec.read(BUFFER+512,1010)==pcm;checks+=1
        assert remaining==0 and digest.hexdigest()==track['ffmpeg_decoded_pcm16_sha256']
        host.append({'id':track['id'],'all_samples_match_ffmpeg_sha256':True,'samples':info['samples']})
    fixture={n:wave_fixture(b) for n,b in raw.items()};expected={n:decode(b[60:316])[:1000] for n,b in fixture.items()}
    for name,data in raw.items():
        player=Player(raw);player.scene(['menu.wav','strategy.wav','battle.wav'].index(name)+1)
        head=b''.join(decode(data[o:o+256]) for o in range(60,60+256*9,256))
        assert player.output==head[:1024] and len(player.handles)==1;player.stop();assert not player.handles;checks+=1
    p=Player(fixture);p.scene(1)
    for _ in range(7):p.poll()
    assert p.output==(expected['menu.wav']*9)[:8192];checks+=1
    # C200 applies its current attenuation to the caller's writable PCM.
    # Regenerating the next buffer must never reuse that already-scaled data.
    volume=Player(fixture);volume.attenuate_in_place=True;volume.scene(1);volume.poll()
    assert volume.output==(expected['menu.wav']*3)[:2048];volume.stop();checks+=1
    # Same scene continues rather than reopening; changing scenes closes old
    # audio/file before opening the next, and preserves1024-byte write order.
    before=len([x for x in p.log if x[0]=='open']);p.poll();p.scene(1)
    assert len([x for x in p.log if x[0]=='open'])==before;checks+=1
    for scene,name in [(2,'strategy.wav'),(3,'battle.wav'),(2,'strategy.wav'),(1,'menu.wav')]:
        p.output.clear();p.capacity=8;p.scene(scene);assert p.output==(expected[name]*2)[:1024] and len(p.handles)==1;checks+=1
    p.stop();last=list(p.log);p.stop();p.poll();assert p.log==last and not p.handles;checks+=1
    for limit in [0,256,1024]:
        p=Player(fixture);p.limit=limit;p.scene(1)
        assert p.output==(expected['menu.wav']*9)[:len(p.output)]
        p.limit=1024;p.poll();assert p.output==(expected['menu.wav']*20)[:len(p.output)];p.stop();checks+=1
    p=Player(fixture);p.capacity=0;p.scene(1);assert not p.output;p.poll(1);assert p.output==(expected['menu.wav']*2)[:1024];p.stop();checks+=1
    p=Player(fixture);p.read_limit=7;p.scene(1);assert p.output==(expected['menu.wav']*2)[:1024];p.stop();checks+=1
    p=Player({});p.scene(1);p.poll();p.poll();assert p.log==[('open','menu.wav')];p.stop();checks+=1
    p=Player(fixture,frame=0);p.scene(1);assert not p.log;checks+=1
    mutations=[(0,b'NOPE'),(4,b'\0'*4),(20,b'\1\0'),(22,b'\2\0'),(24,struct.pack('<I',44100)),(32,struct.pack('<H',128)),(34,b'\x10\0'),(38,b'\0\0'),(48,b'\0'*4),(56,struct.pack('<I',255)),(62,b'\x59'),(63,b'\1')]
    for offset,value in mutations:
        bad=bytearray(fixture['menu.wav']);bad[offset:offset+len(value)]=value;p=Player({'menu.wav':bytes(bad)});p.scene(1)
        assert not p.output and not p.handles,offset;p.stop();checks+=1
    p=Player(fixture);p.fail_seek=True;p.scene(1);assert not p.handles and not p.output;checks+=1
    p=Player(fixture);p.write_error=True;p.scene(1);assert not p.handles and ('audio-stop',) in p.log;checks+=1
    p=Player(fixture);p.clock=0xfffffff8;p.scene(1);size=len(p.output);p.poll(elapsed=0);assert len(p.output)==size+1024;p.poll(elapsed=8);assert len(p.output)==size+2048;p.stop();checks+=1
    # One call cannot monopolize input with eight potentially blocking writes.
    p=Player(raw);p.scene(1);assert len([x for x in p.log if x[0]=='write'])==1
    for _ in range(12):
        before=len(p.output);p.poll();assert len(p.output)-before==1024
    p.stop();checks+=1
    # 32 PCM buffers consume33 ADPCM blocks;4KiB read-ahead needs only3 reads.
    p=Player(raw);p.scene(1)
    for _ in range(31):p.poll()
    large=[x for x in p.log if x[0]=='read' and x[1]>256]
    expected_head=b''.join(decode(raw['menu.wav'][60+i*256:60+(i+1)*256]) for i in range(33))
    assert len(large)==3 and all(x[1]==4096 for x in large) and p.output==expected_head[:32768]
    p.stop();checks+=1
    # Music timer callbacks must leave the game's pending event words intact.
    p=Player(fixture);names=['g_native_event_kind','g_native_event_key','g_native_event_data']
    for name,value in zip(names,[5,28,123]):p.m.word(STATE[name],value)
    assert p.m.call('sango_window_proc',123,0x144,3,0)==1
    assert [struct.unpack('<I',p.m.read(STATE[n],4))[0] for n in names]==[5,28,123];checks+=1
    pending=[(0,3,0),(0x10,28,0)]
    def event(a):p.m.write(a[0],struct.pack('<III',*pending.pop(0)));return 1
    p.m.intercept('sango_input_poll_native_event',1,event);p.m.call('sango_input_next_event',BUFFER)
    assert struct.unpack('<II',p.m.read(BUFFER,8))==(5,28) and not pending;checks+=1
    # Actual game entry/return hooks, including automatic battles which keep
    # the strategy soundtrack instead of briefly interrupting it.
    for function,mode,scenes in [('sango_select_session',0,[1]),('sango_strategy_run_months',0,[2]),('sango_battle_run',1,[3,2]),('sango_battle_run',2,[2,2])]:
        m=Machine((ROOT/'build/sango.elf').read_bytes());seen=[]
        m.intercept('sango_music_set_scene',1,lambda a:seen.append(a[0]))
        if function=='sango_select_session':m.intercept('sango_menu_select_animated',2,lambda a:3)
        elif function=='sango_strategy_run_months':
            m.intercept('sango_strategy_player_has_no_cities',0,lambda a:1)
            m.intercept('sango_ui_show_strategy_text',1,lambda a:None)
        else:
            m.write(STATE['g_battle_control_mode'],bytes([mode]))
            m.intercept('sango_battle_initialize_unit_stats',0,lambda a:m.write(STATE['g_battle_result_view2'],b'\1'))
        m.call(function);assert seen==scenes,(function,seen);checks+=1
    report={'passed':checks,'failed':0,'bda_sha256':hashlib.sha256((ROOT/'build/三国霸业.bda').read_bytes()).hexdigest(),
            'music_bytes':sum(t['bytes'] for t in manifest['tracks']),'full_track_ffmpeg_oracles':host,
            'scope':'All bundled music samples match saved independent FFmpeg decoder hashes. Selected real MIPS blocks plus full real-MIPS streaming/header/loop/scene/short-write/backpressure/failure/close paths. SDK file/audio/time boundaries modeled; native audio checked separately. Music timer cannot replace pending input or become a game tick.'}
    (ROOT/'build/music-validation.json').write_text(json.dumps(report,ensure_ascii=False,indent=2)+'\n',encoding='utf8',newline='\n')
    print(json.dumps(report))


if __name__=='__main__':main()
