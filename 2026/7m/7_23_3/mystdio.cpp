#include "mystdio.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

static MyFile* BuyFile(int fd, int flag)
{
    MyFile* f = (MyFile*)malloc(sizeof(MyFile));
    if(f == NULL) return NULL;

    f->bufferlen = 0;
    f->fileno = fd;
    f->flag = flag;
    f->flush_method = LINE_FLUSH;

    memset(f->outbuffer, 0, sizeof(f->outbuffer));

    return f;
}

MyFile* MyFopen(const char* path, const char* mode)
{
    int fd = -1;
    int flag = 0;

    if(strcmp(mode, "w") == 0)
    {
        flag = O_CREAT | O_WRONLY | O_TRUNC;
        fd = open(path, flag, 0666);
    }
    else if(strcmp(mode, "a") == 0)
    {
        flag = O_CREAT | O_WRONLY | O_APPEND;
        fd = open(path, flag, 0666);
    }
    else if(strcmp(mode, "r") == 0)
    {
        flag = O_RDONLY;
        fd = open(path, flag);
    }
    else
    {
        return NULL;
    }

    if(fd < 0) return NULL;

    return BuyFile(fd, flag);
}

void MyFclose(MyFile* file)
{
    if(file == NULL) return;
    if(file->fileno < 0) return;

    MyFFlush(file);
    close(file->fileno);
    free(file);
}

int MyFwrite(MyFile* file, const void* str, int len)
{
    if(file == NULL || str == NULL || len <= 0) return -1;

    memcpy(file->outbuffer + file->bufferlen, str, len);
    file->bufferlen += len;

    if((file->flush_method & LINE_FLUSH) &&
       file->outbuffer[file->bufferlen - 1] == '\n')
    {
        MyFFlush(file);
    }

    return len;
}

void MyFFlush(MyFile* file)
{
    if(file == NULL) return;
    if(file->fileno < 0) return;
    if(file->bufferlen <= 0) return;

    int n = write(file->fileno, file->outbuffer, file->bufferlen);
    (void)n;

    fsync(file->fileno);

    file->bufferlen = 0;
    memset(file->outbuffer, 0, sizeof(file->outbuffer));
}