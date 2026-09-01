#include <iostream>
#include <pthread.h>
#include <unistd.h>

int g_val = 100;

void *ThreadRun(void *args) {
  int local = 10;
  int *heap_val = (int *)args;

  std::cout << "子线程: " << std::endl;
  std::cout << "&g_val   = " << &g_val << std::endl;
  std::cout << "heap_val = " << heap_val << std::endl;
  std::cout << "&local   = " << &local << std::endl;
  return nullptr;
}

int main() {
  int main_local = 20;
  int *p = new int(30);
  pthread_t tid;
  pthread_create(&tid, nullptr, ThreadRun, p);

  std::cout << "主线程: " << std::endl;
  std::cout << "&g_val   = " << &g_val << std::endl;
  std::cout << "heap_val = " << p << std::endl;
  std::cout << "&local   = " << &main_local << std::endl;

  pthread_join(tid, nullptr);
  delete p;
  return 0;
}
