#include "test_framework/generic_test.h"
long long Reverse(int x) {
  bool is_negative = false;
  long long reverse = 0;

  if(x < 0){
    is_negative = true;
    x = -x;
  }

  while(x){
    reverse = reverse * 10 + (x % 10);
    x /= 10;
  }

  return is_negative ? -reverse : reverse;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "reverse_digits.cc", "reverse_digits.tsv",
                         &Reverse, DefaultComparator{}, param_names);
}
