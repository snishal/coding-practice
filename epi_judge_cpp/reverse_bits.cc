#include "test_framework/generic_test.h"
unsigned long long ReverseBits(unsigned long long x) {
  unsigned long long reverse = 0;
  
  for(int i = 0; i <= 31; i++){
    if(((x >> i) & 1) != ((x >> 64 - i - 1) & 1)){
      unsigned long long mask = (1 << i) | (1 << 64 - i - 1);
      x ^= mask;
    }
  }

  return x;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "reverse_bits.cc", "reverse_bits.tsv",
                         &ReverseBits, DefaultComparator{}, param_names);
}
