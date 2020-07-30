#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

int FindKthLargestUnknownLength(vector<int>::const_iterator stream_begin,
                                const vector<int>::const_iterator& stream_end,
                                int k) {
  // TODO - you fill in here.
  vector<int> candidates;
  while(stream_begin != stream_end){
    candidates.emplace_back(*stream_begin++);
    if(candidates.size() == 2 * k - 1){
      std::nth_element(candidates.begin(), candidates.begin() + k - 1, candidates.end(), std::greater<int>());
      candidates.resize(k);
    }
  }
  std::nth_element(candidates.begin(), candidates.begin() + k - 1, candidates.end(), std::greater<int>());

  return candidates[k - 1];
}
int FindKthLargestUnknownLengthWrapper(const vector<int>& stream, int k) {
  return FindKthLargestUnknownLength(stream.cbegin(), stream.cend(), k);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"stream", "k"};
  return GenericTestMain(args, "kth_largest_element_in_long_array.cc",
                         "kth_largest_element_in_long_array.tsv",
                         &FindKthLargestUnknownLengthWrapper,
                         DefaultComparator{}, param_names);
}
