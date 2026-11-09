typedef unsigned int u32;
static u32 positions[4];
static const u32 sizes[4]={0,2932796,1229628,1672508};
static const u32 addresses[4]={0,0x85000000,0x852cc03c,0x853f8378};
int fixture_file_open(const char *path) {
 const char *last=path;while(*path){if(*path=='\\'||*path=='/')last=path+1;path++;}
 unsigned int file=*last=='m'?1:*last=='s'?2:*last=='b'?3:0;
 positions[file]=0;return file;
}
void fixture_file_close(unsigned int file){positions[file]=0;}
int fixture_file_seek(unsigned int file,int offset,int whence){
 int value=(whence==2?sizes[file]:whence==1?positions[file]:0)+offset;
 if(!file||value<0||(u32)value>sizes[file])return -1;positions[file]=value;return value;
}
int fixture_file_read(unsigned int file,unsigned char *out,unsigned int count){
 unsigned int left=sizes[file]-positions[file];if(count>left)count=left;
 const unsigned char *data=(const unsigned char*)(addresses[file]+positions[file]);
 for(unsigned int i=0;i<count;i++)out[i]=data[i];positions[file]+=count;return count;
}