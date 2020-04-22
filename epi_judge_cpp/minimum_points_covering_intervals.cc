#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
using std::vector;

struct Interval {
  int left, right;
};

int FindMinimumVisits(vector<Interval> intervals) {
  
  sort(intervals.begin(), intervals.end(), 
    [](const Interval& i1, const Interval& i2) {
      return i1.right < i2.right;
    }
  );

  int i = 0, min_visits = 0;

  while(i < intervals.size()){
    min_visits++;
    int j = i + 1;
    while(j < intervals.size() && intervals[j].left <= intervals[i].right){
      j++;
    };
    i = j;
  }

  return min_visits;
}
namespace test_framework {
template <>
struct SerializationTrait<Interval> : UserSerTrait<Interval, int, int> {};
}  // namespace test_framework

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"intervals"};
  return GenericTestMain(args, "minimum_points_covering_intervals.cc",
                         "minimum_points_covering_intervals.tsv",
                         &FindMinimumVisits, DefaultComparator{}, param_names);
}
