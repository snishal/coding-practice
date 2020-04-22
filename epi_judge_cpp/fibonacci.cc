#include "test_framework/generic_test.h"
int Fibonacci(int n) {
  if(n <= 1){
    return n;
  }

  int f[2] = {0, 1};

  for(int i = 2; i <= n; i++){
    int fib = f[0] + f[1];
    std::swap(f[0], f[1]);
    f[1] = fib;
  }

  return f[1];
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n"};
  return GenericTestMain(args, "fibonacci.cc", "fibonacci.tsv", &Fibonacci,
                         DefaultComparator{}, param_names);
}
