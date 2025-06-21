#include <stdio.h>

int main()
{
    FILE *fp;
    fp = fopen("log.txt", "w+");
    for (int i = 0; i < 9; i++)
    {
        fprintf(fp, "%d\n", i);
    }
    fclose(fp);
    return 0;
}