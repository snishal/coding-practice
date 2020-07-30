#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

struct Subarray {
  int start = 0, end = 0;

  bool operator>(const Subarray& that){
    return (end - start + 1) > (that.end - that.start + 1);
  }
};

Subarray FindLongestIncreasingSubarray(const vector<int>& A) {
  Subarray longestSubarray = Subarray({-1, -1}), subarray = Subarray({0, 0});

  for(int i = 1; i < A.size(); i++){
    if(A[i - 1] < A[i]){
      subarray.end = i;
    }else{
      if(subarray > longestSubarray){
        longestSubarray = subarray;
      }
      subarray.start = i, subarray.end = i;
    }
  }
  if(subarray > longestSubarray){
    longestSubarray = subarray;
  }

  return longestSubarray;
}
int FindLongestIncreasingSubarrayWrapper(const vector<int>& A) {
  Subarray result = FindLongestIncreasingSubarray(A);
  return result.end - result.start + 1;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(
      args, "longest_increasing_subarray.cc", "longest_increasing_subarray.tsv",
      &FindLongestIncreasingSubarrayWrapper, DefaultComparator{}, param_names);
}
