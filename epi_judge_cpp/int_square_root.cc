#include "test_framework/generic_test.h"

int SquareRoot(int k) {
  int l = 0, r = k;
  while(l <= r){
    long m = l + (r - l) / 2;
    long m_sq = m * m;
    if(m_sq <= k){
      l = m + 1;
    }else{
      r = m - 1;
    }
  }
  return l - 1;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"k"};
  return GenericTestMain(args, "int_square_root.cc", "int_square_root.tsv",
                         &SquareRoot, DefaultComparator{}, param_names);
}
