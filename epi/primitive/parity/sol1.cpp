#include "test_framework/generic_test.h"
short Parity(unsigned long long x) {
  short parity = 0;
  while(x){
	parity ^= 1;
	x &= (x - 1);
  }
  return parity;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "parity.cc", "parity.tsv", &Parity,
                         DefaultComparator{}, param_names);
}
