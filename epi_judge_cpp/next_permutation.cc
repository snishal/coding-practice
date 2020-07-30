#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
vector<int> NextPermutation(vector<int> perm) {
  int i;
  for(i = perm.size() - 2; i >= 0; i--){
    if(perm[i] < perm[i + 1]){
      break;
    }
  }
  if(i == -1){
    return {};
  }

  for(int j = perm.size() - 1; j > i; j--){
    if(perm[i] < perm[j]){
      std::swap(perm[i], perm[j]);
      break;
    }
  }

  std::reverse(perm.begin() + i + 1, perm.end());
  return perm;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"perm"};
  return GenericTestMain(args, "next_permutation.cc", "next_permutation.tsv",
                         &NextPermutation, DefaultComparator{}, param_names);
}
