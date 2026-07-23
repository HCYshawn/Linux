#include"mystdio.h"
#include<sys/types.h>
#include<sys/stat.h>
#include<cntl.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

static MyFile *BuyFile(int fd,int flag)
{
    MyFile *f = (MyFile*)malloc(sizeof(MyFile));
    if(f==NULL)return NULL;
    f->bufferlen = 0;
    f->fileno = fd;
    f->flag = flag;
    f->flush_method = LINE_FLUSH;
    memset(f->outbuffer,0,sizeof(f->outbuffer));
}

MyFile* MyFopen(const char* path,const char* mode)
{
    int fd = -1;
    if(strcmp(mode,"w" == 0))
    {
        flag = O_CREAT | O_WRONLY | O_TRUNC;
        fd = open(path,flag,0666);
    }
    else if(strcmp(mode,"a" == 0))
    {
        flag = O_CREAT | O_WRONLY | O_APPEND;
        fd = open(path,flag,0666);
    }
    else if(strcmp(mode,"e" == 0))
    {
        flag = O_RDWR;
        fd = open(path,flag);
    }
    else
    {

    }

    if(fd < 0)return NULL;


    return BuyFile(fd,flag);
}

void MyFclose(MyFile*)
{

}

int MyFwrite(MyFile*,void *str,int len)
{
    memcpy(file->outbuffer+file->bufferlen,str,len);
    file->bufferlen += len;
    if((file->flush_method & LINE_FLUSH)&&file->outbuffer[file->bufferlen-1]=='\n')
    {
        MyFlush(file);
    }
    return 0;
}

void MyFlush(MyFile*file)
{
    int n = write(file->fileno,file->outbuffer,file->bufferlen);
    (void)n;
    file->bufferlen = 0;
}
