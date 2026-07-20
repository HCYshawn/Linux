#include <cstdio>
#include <cstring>

int main() {
  FILE *fp = fopen("log.txt", "w");
  if (fp == NULL) {
    perror("fopen");
    return 1;
  }
  const char *msg = "hello file: ";
  int cnt = 1;
  while (cnt <= 10) {
    char buffer[1024];
    snprintf(buffer, sizeof(buffer), "%s%d\n", msg, cnt++);
    fwrite(buffer, strlen(buffer), 1, fp);
  }
  fclose(fp);
  return 0;
}
