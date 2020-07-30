#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

bool HasTwoSum(const vector<int>& A, int t) {
  // TODO - you fill in here.
  int i = 0, j = A.size() - 1;
  while(i <= j){
    int sum = A[i] + A[j];
    if(sum == t){
      return true;
    }else if(sum < t){
      ++i;
    }else{
      --j;
    }
  }
  return false;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "t"};
  return GenericTestMain(args, "two_sum.cc", "two_sum.tsv", &HasTwoSum,
                         DefaultComparator{}, param_names);
}
