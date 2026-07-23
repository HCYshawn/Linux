#include "mystdio.h"
#include <string.h>

int main()
{
    MyFile* filep = MyFopen("./log.txt", "a");
    if(!filep)
    {
        printf("MyFopen error!\n");
        return 1;
    }

    const char* msg = "hello myfile!\n";
    MyFwrite(filep, msg, strlen(msg));

    MyFclose(filep);

    return 0;
}