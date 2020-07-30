#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

int MaxSubarraySum(const vector<int>& A, const int& (*comp)(const int&, const int&)){
  int till = 0, overall = 0;
  for(const int& a : A){
    till = comp(a, a + till);
    overall = comp(overall, till);
  }
  return overall;
}

int MaxSubarraySumInCircular(const vector<int>& A) {
  // TODO - you fill in here.
  return std::max(MaxSubarraySum(A, std::max), std::accumulate(A.begin(), A.end(), 0) - MaxSubarraySum(A, std::min));
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "maximum_subarray_in_circular_array.cc",
                         "maximum_subarray_in_circular_array.tsv",
                         &MaxSubarraySumInCircular, DefaultComparator{},
                         param_names);
}
