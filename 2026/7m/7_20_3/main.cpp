#include <cstdio>
#include <cstring>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage: %s filename\n", argv[0]);
    return 1;
  }

  FILE *fp = fopen(argv[1], "r");
  if (fp == NULL) {
    perror("fopen");
    return 2;
  }

  while (1) {
    char buffer[128];
    memset(buffer, 0, sizeof(buffer));
    int n = fread(buffer, sizeof(buffer) - 1, 1, fp);
    if (n > 0) {

      printf("%s", buffer);
    }
    if (feof(fp))
      break;
  }

  fclose(fp);
  return 0;
}
