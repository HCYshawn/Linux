#include "calculator.h"
#include "addsub.h"
#include "muldiv.h"

int compute_add_mul(int a, int b) {
  int sum = add(a, b);
  int prod = mul(a, b);
  return sum + prod;
}
