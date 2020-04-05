#include "test_framework/generic_test.h"
unsigned long long ClosestIntSameBitCount(unsigned long long x) {
  const int numBits = 64;
  for(int i = 0; i < numBits; i++){
    if((x >> i & 1L) != (x >> i + 1 & 1L)){
      x ^= (1L << i) | (1L << i + 1);
      return x;
    }
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "closest_int_same_weight.cc",
                         "closest_int_same_weight.tsv", &ClosestIntSameBitCount,
                         DefaultComparator{}, param_names);
}
