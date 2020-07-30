#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

int LongestNondecreasingSubsequenceLength(const vector<int>& A) {
  // TODO - you fill in here.
  int max_len = 1;
  vector<int> longest_with_this(A.size(), 1);

  for(int i = 1; i < A.size(); ++i){
    for(int j = 0; j < i; ++j){
      if(A[j] <= A[i]){
        longest_with_this[i] = std::max(longest_with_this[i], longest_with_this[j] + 1);
      }
    }
    max_len = std::max(max_len, longest_with_this[i]);
  }

  return max_len;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "longest_nondecreasing_subsequence.cc",
                         "longest_nondecreasing_subsequence.tsv",
                         &LongestNondecreasingSubsequenceLength,
                         DefaultComparator{}, param_names);
}
