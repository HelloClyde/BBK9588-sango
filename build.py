"""Build the Sango C reconstruction using the pinned BBK 9588 SDK."""
from __future__ import annotations
import argparse,hashlib,json,os,shutil,subprocess,sys
from pathlib import Path

ROOT=Path(__file__).resolve().parent
SDK_COMMIT='ef3bf3b7328a3a8fa9ba48593c63285300725fb7'
SOURCES=['sango_engine','sango_data','sango_entry','sango_statusbar','sango_credits','sango_battle_ui','sango_color','sango_color_sdk','sango_color_animation','sango_touch','sango_battle_info','sango_music','sango_music_sdk','sango_ui_paint','sango_intro','sango_ruler','sango_settings']

def command(args,**kwargs):
    return subprocess.run([str(x) for x in args],check=True,**kwargs)

def sdk_revision():
    return subprocess.check_output(['git','-C',str(ROOT/'sdk'),'rev-parse','HEAD'],text=True).strip()

def compiler(explicit):
    value=explicit or os.environ.get('SANGO_CC') or shutil.which('mipsel-none-elf-gcc')
    candidates=[Path(value)] if value else []
    candidates += [ROOT/'sdk/.toolchain/bin/mipsel-none-elf-gcc.exe',
        ROOT/'sdk/.toolchain/g++-mipsel-none-elf-15.2.0/bin/mipsel-none-elf-gcc.exe']
    for p in candidates:
        if p.is_file():return p.resolve()
    raise SystemExit('Run sdk/scripts/setup_toolchain.ps1, set SANGO_CC, or pass --cc.')

def make_header(payload):
    from bda_packer.header import BdaHeaderFields,write_header,fix_header_checksum
    from bda_packer.vx_icon import ICON_SPECS,read_png,rgb565_bytes,make_vx
    prefix=bytearray(0x88);sizes=[]
    for i,(w,h) in enumerate(ICON_SPECS):
        sw,sh,pixels=read_png(ROOT/'assets/app-icon'/f'icon-{i}-{w}x{h}.png')
        if (sw,sh)!=(w,h):raise ValueError('Incorrect pre-generated icon dimensions')
        block=make_vx(w,h,rgb565_bytes(pixels,(255,255,255),transparent_key=None))
        prefix.extend(block);sizes.append(len(block))
    if len(prefix)!=0x95f8:raise ValueError('Unexpected original loader layout')
    data=prefix+payload
    data.extend(bytes((-len(data))%4));data.extend(bytes(4))
    fields=BdaHeaderFields(category=4,file_size_minus_4=len(data)-4,
        entry_offset=len(prefix),icon_start=0x88,
        icon0_size=sizes[0],icon1_size=sizes[1],icon2_size=sizes[2],icon3_size=sizes[3])
    write_header(data,fields,'三国霸业')
    # Preserve the original container's descriptive metadata, not a build-time
    # timestamp. This keeps the already validated BDA byte-for-byte stable.
    metadata=json.loads((ROOT/'assets/container-metadata.json').read_text(encoding='utf-8'))
    stamp=metadata['original_build_stamp'].encode('ascii')
    message=metadata['minimum_os_message'].encode('gbk')
    if len(stamp)>19 or len(message)>51:raise ValueError('Invalid container metadata')
    data[0x3c:0x50]=stamp.ljust(20,b'\0')
    data[0x50:0x84]=message.ljust(52,b'\0')
    fix_header_checksum(data)
    return bytes(data)

def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--cc');p.add_argument('--music-diagnostics',action='store_true');args=p.parse_args()
    if not (ROOT/'sdk/sdk/include/bda_sdk.h').is_file():
        raise SystemExit('Initialize the pinned SDK: git submodule update --init sdk')
    revision=sdk_revision()
    if revision!=SDK_COMMIT:raise SystemExit('SDK does not match the verified commit')
    command(['git','-C',ROOT/'sdk','diff','--quiet',SDK_COMMIT,'--','sdk/include','bda_packer'])
    sys.path.insert(0,str(ROOT/'sdk'))
    from bda_packer.validate import validate_bda
    cc=compiler(args.cc);out=ROOT/'build';out.mkdir(exist_ok=True)
    from tools.sango_lib import pack,generate_includes
    library=pack(ROOT/'assets/library')
    (out/'sango.lib').write_bytes(library)
    generate_includes(ROOT/'assets/library',ROOT/'include')
    from tools.color_assets import build as build_color
    color = build_color(out/'sango.clr')
    from tools.music_assets import validate as validate_music
    music=validate_music();(out/'music').mkdir(exist_ok=True)
    music_files=[]
    for track in music['tracks']:
        name=track['id']+'.wav'
        shutil.copy2(ROOT/'assets/music'/track['path'],out/'music'/name)
        music_files.append({'id':track['id'],'file':name,'bytes':track['bytes'],
                            'sha256':track['sha256'],'samples':track['samples'],
                            'duration_seconds':track['duration_seconds']})
    (out/'music-build.json').write_text(json.dumps(music,ensure_ascii=False,indent=2)+'\n',encoding='utf8',newline='\n')
    from tools.build_engine import write_unity,add_legacy_debug_symbols
    write_unity(out/'sango_engine.c')
    flags=['-std=gnu99','-EL','-march=mips32','-mabi=32','-msoft-float','-mno-abicalls',
        '-G0','-fno-pic','-ffreestanding','-fno-builtin','-fno-strict-aliasing','-fwrapv',
        '-Os','-ffunction-sections','-fdata-sections','-Wno-incompatible-pointer-types',
        '-Wno-int-conversion','-I',ROOT/'include','-I',ROOT/'sdk/sdk/include']
    objects=[]
    if args.music_diagnostics:flags+=['-DSANGO_MUSIC_DIAGNOSTICS=1']
    for name in SOURCES:
        source=out/'sango_engine.c' if name=='sango_engine' else ROOT/'src'/(name+'.c')
        obj=out/(name+'.o');command([cc,*flags,'-c',source,'-o',obj]);objects.append(obj)
    elf=out/'sango.elf'
    command([cc,'-EL','-march=mips32','-mabi=32','-msoft-float','-mno-abicalls','-fno-pic',
        '-nostdlib','-Wl,--gc-sections','-Wl,--build-id=none','-Wl,-Map,'+str(out/'sango.map'),
        '-Wl,-T,'+str(ROOT/'sango.ld'),*objects,'-lgcc','-o',elf])
    raw=out/'sango.bin';objcopy=cc.with_name(cc.name.replace('gcc','objcopy'))
    add_legacy_debug_symbols(cc,elf)
    command([objcopy,'-O','binary',elf,raw])
    data=make_header(raw.read_bytes());bda=out/'三国霸业.bda';bda.write_bytes(data)
    validation=validate_bda(bda);validation['path']='build/三国霸业.bda'
    if not validation['ok'] or validation['warnings']:raise SystemExit(json.dumps(validation))
    (out/'sdk-validation.json').write_text(json.dumps(validation,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
    reference=json.loads((ROOT/'validation/reference-build.json').read_text(encoding='utf-8'))
    result={'bda':'build/三国霸业.bda','bytes':len(data),'sha256':hashlib.sha256(data).hexdigest(),
        'library':'build/sango.lib','library_bytes':len(library),'library_sha256':hashlib.sha256(library).hexdigest(),
        'color':'build/sango.clr','color_bytes':color['bytes'],'color_sha256':color['sha256'],
        'color_frames':color['frames'],
        'music_bytes':music['bytes'],'music':music_files,
        'sdk_commit':revision,'compiler':subprocess.check_output([str(cc),'--version'],text=True).splitlines()[0],
        'matches_runtime_reference':hashlib.sha256(data).hexdigest()==reference['bda_sha256'],
        'matches_library_reference':hashlib.sha256(library).hexdigest()==reference.get('sango_lib_sha256'),
        'matches_color_reference':color['sha256']==reference.get('sango_clr_sha256')}
    (out/'build-result.json').write_text(json.dumps(result,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
    # JSON escapes keep redirected Windows logs valid under non-Chinese locales.
    print(json.dumps(result,indent=2))

if __name__=='__main__':main()
