#include "test_framework/generic_test.h"

unsigned long long Add(unsigned long long x, unsigned long long y) {
  unsigned long long sum = 0, carry = 0, k = 1, temp_x = x, temp_y = y;
  while(temp_x || temp_y){
    unsigned long long xk = x & k, yk = y & k;
    unsigned long long carryout = (xk & yk) | (xk & carry) | (yk & carry);
    sum |= (xk ^ yk ^ carry);
    carry = carryout << 1, k <<= 1, temp_x >>= 1, temp_y >>= 1;
  }

  return sum | carry;
}

unsigned long long Multiply(unsigned long long x, unsigned long long y) {
  unsigned long long res = 0;

  while(y){
    if(y & 1){
      res = Add(res, x);
    }
    x <<= 1;
    y >>= 1;
  }

  return res;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x", "y"};
  return GenericTestMain(args, "primitive_multiply.cc",
                         "primitive_multiply.tsv", &Multiply,
                         DefaultComparator{}, param_names);
}
