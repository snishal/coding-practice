#include <vector>
#include <unordered_map>

#include "test_framework/generic_test.h"
using std::vector;
using std::unordered_map;

int LongestSubarrayWithDistinctEntries(const vector<int>& A) {
  if(A.empty()){
    return 0;
  }
  unordered_map<int, int> rightMost;

  int start = 0, longest = 1;
  for(int i = 0; i < A.size(); i++){
    if(rightMost.count(A[i])){
      longest = std::max(longest, i - start);
      start = std::max(start, rightMost[A[i]] + 1);
    }
    rightMost[A[i]] = i;
  }
  longest = std::max(longest, static_cast<int>(A.size()) - start);
  
  return longest;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "longest_subarray_with_distinct_values.cc",
                         "longest_subarray_with_distinct_values.tsv",
                         &LongestSubarrayWithDistinctEntries,
                         DefaultComparator{}, param_names);
}
