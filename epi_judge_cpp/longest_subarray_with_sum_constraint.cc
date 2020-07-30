#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

int FindLongestSubarrayLessEqualK(const vector<int>& A, int k) {
  // TODO - you fill in here.
  vector<int> prefix_sum;
  std::partial_sum(A.begin(), A.end(), std::back_inserter(prefix_sum));

  if(prefix_sum.back() <= k){
    return A.size();
  }

  vector<int> min_prefix_sum(A.size());
  min_prefix_sum.back() = prefix_sum.back();
  for(int i = A.size() - 2; i >= 0; --i){
    min_prefix_sum[i] = std::min(prefix_sum[i], min_prefix_sum[i + 1]);
  }

  int i = 0, j = 0, max_len = 0;
  while(i < A.size() && j < A.size()){
    int sum = i > 0 ? min_prefix_sum[j] - prefix_sum[i - 1] : min_prefix_sum[j];
    if(sum <= k){
      int len = j - i + 1;
      if(len > max_len){
        max_len = len;
      }
      ++j;
    }else{
      ++i;
    }
  }

  return max_len;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "k"};
  return GenericTestMain(args, "longest_subarray_with_sum_constraint.cc",
                         "longest_subarray_with_sum_constraint.tsv",
                         &FindLongestSubarrayLessEqualK, DefaultComparator{},
                         param_names);
}
