#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main() {
  int fd = open("log.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
  if (fd < 0) {
    perror("open");
    return 1;
  }
  FILE *fp = fdopen(fd, "w");
  if (fp == NULL) {
    perror("fdopen");
    close(fd);
    return 2;
  }

  fprintf(fp, "hello fdopen\n");

  fclose(fp);
  return 0;
}
