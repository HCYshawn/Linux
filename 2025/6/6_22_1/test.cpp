#include <stdio.h>

int main()
{
    FILE *fp;
    fp = fopen("log", "w+");
    int arr[10] = {0};
    for (int i = 1; i <= 9; i++)
    {
        fprintf(fp, "%d\n", i * i);
    }
    rewind(fp);
    for (int i = 0; i < 9; i++)
    {
        fscanf(fp, "%d", &arr[i]);
    }
    fclose(fp);
    for (int i = 0; i < 10; i++)
    {
        printf("%d\n", arr[i]);
    }
    return 0;
}