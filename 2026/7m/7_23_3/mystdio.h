#pragma once

#include <stdio.h>

#define MAX 1024

#define NONE_FLUSH (1<<0)
#define LINE_FLUSH (1<<1)
#define FULL_FLUSH (1<<2)

typedef struct IO_FILE
{
    int fileno;
    int flag;
    char outbuffer[MAX];
    int bufferlen;
    int flush_method;
} MyFile;

MyFile* MyFopen(const char* path, const char* mode);
void MyFclose(MyFile* file);
int MyFwrite(MyFile* file, const void* str, int len);
void MyFFlush(MyFile* file);