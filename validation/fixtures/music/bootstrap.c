#include "sango_internal.h"
#include "bda_sdk.h"
#define PLAYER ((volatile unsigned char*)0x81c2d670)
#define MARK (*(volatile unsigned int*)0x81c3f000)
uint32_t fixture_entry(uint16_t id) {
 if(!sango_color_use_buffer((void*)0x81400000,2297312,461116))return 0;
 sango_animation_play_resource(id);
 const char *paths[]={"\x41\x3a\x5c\xd3\xa6\xd3\xc3\x5c\xca\xfd\xbe\xdd\x5c\xd3\xce\xcf\xb7\x5c\x73\x61\x6e\x67\x6f\x2d\x6d\x75\x73\x69\x63\x5c""menu.wav","\x41\x3a\x5c\xd3\xa6\xd3\xc3\x5c\xca\xfd\xbe\xdd\x5c\xd3\xce\xcf\xb7\x5c\x73\x61\x6e\x67\x6f\x2d\x6d\x75\x73\x69\x63\x5c""strategy.wav","\x41\x3a\x5c\xd3\xa6\xd3\xc3\x5c\xca\xfd\xbe\xdd\x5c\xd3\xce\xcf\xb7\x5c\x73\x61\x6e\x67\x6f\x2d\x6d\x75\x73\x69\x63\x5c""battle.wav"};
 for(unsigned int i=0;i<3;i++) {
  unsigned int *record=(unsigned int*)(0x81c3e000+i*336);
  int file=bda_fs_fopen_raw(paths[i],"rb");record[0]=file;
  if(bda_fs_file_is_valid(file)) {
   record[1]=bda_fs_seek_raw(file,0,BDA_SEEK_END);bda_fs_seek_raw(file,0,BDA_SEEK_SET);
   record[2]=bda_fs_read_raw(file,record+3,316);bda_fs_close_raw(file);
  }
 }
 for(unsigned int scene=1;scene<=3;scene++) {
  unsigned int start;int event[3];
  sango_music_set_scene(scene);MARK=scene;start=sango_music_sdk_clock();
  while(sango_music_sdk_clock()-start<1000) sango_input_poll_native_event((void*)event);
  volatile unsigned char *record=(volatile unsigned char*)(0x81c3c000+(scene-1)*1152);
  for(unsigned int j=0;j<60;j++)record[j]=PLAYER[j];
  ((volatile unsigned int*)record)[15]=bda_audio_get_attenuation();
  for(unsigned int j=0;j<1024;j++)record[64+j]=PLAYER[1550+j];
 }
 sango_music_shutdown();MARK=4;for(;;)sango_input_wait(0,1);
}