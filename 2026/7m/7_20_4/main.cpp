#include <cstdio>
#include <cstring>

int main() {
  printf("hello printf\n");

  fprintf(stdout, "hello fprintf\n");

  const char *msg = "hello fwrite\n";
  fwrite(msg, strlen(msg), 1, stdout);
  return 0;
}
