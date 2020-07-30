#include <vector>
#include <unordered_set>

#include "test_framework/generic_test.h"
using std::vector;
using std::unordered_set;

int LongestContainedRange(const vector<int>& A) {
  unordered_set<int> s(A.begin(), A.end());
  int max_interval = 0;

  while(!s.empty()){
    int a = *s.begin();
    s.erase(a);

    int lower_bound = a - 1;
    while(s.count(lower_bound)){
      s.erase(lower_bound), --lower_bound;
    }

    int upper_bound = a + 1;
    while(s.count(upper_bound)){
      s.erase(upper_bound), ++upper_bound;
    }

    max_interval = std::max(max_interval, upper_bound - lower_bound - 1);
  }
  return max_interval;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(
      args, "longest_contained_interval.cc", "longest_contained_interval.tsv",
      &LongestContainedRange, DefaultComparator{}, param_names);
}
