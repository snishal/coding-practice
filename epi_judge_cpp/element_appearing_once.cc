#include <vector>
#include <array>

#include "test_framework/generic_test.h"
using std::vector;
using std::array;

int FindElementAppearsOnce(const vector<int>& A) {
  array<int, 32> bit_count = {};

  for(const int& n : A){
    for(int i = 0; i < 32; i++){
      if((n >> i) & 1){
        bit_count[i]++;
      }
    }
  }

  int unique = 0;
  for(int i = 31; i >= 0; i--){
    unique <<= 1;
    if(bit_count[i] % 3 != 0){
      unique |= 1;
    }
  }

  return unique;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "element_appearing_once.cc",
                         "element_appearing_once.tsv", &FindElementAppearsOnce,
                         DefaultComparator{}, param_names);
}
