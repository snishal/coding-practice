#include <vector>

#include "test_framework/fmt_print.h"
#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
using std::vector;

struct Interval {
  int left, right;
};

vector<Interval> AddInterval(const vector<Interval>& disjoint_intervals,
                             Interval new_interval) {
  // TODO - you fill in here.
  int i = 0;
  vector<Interval> mergedIntervals;

  while(i < disjoint_intervals.size() && disjoint_intervals[i].right < new_interval.left){
    mergedIntervals.emplace_back(disjoint_intervals[i++]);
  }

  while(i < disjoint_intervals.size() && disjoint_intervals[i].left <= new_interval.right){
    new_interval = {std::min(new_interval.left, disjoint_intervals[i].left), std::max(new_interval.right, disjoint_intervals[i].right)};
    i++;
  }
  mergedIntervals.emplace_back(new_interval);
  mergedIntervals.insert(mergedIntervals.end(), disjoint_intervals.begin() + i, disjoint_intervals.end());

  return mergedIntervals;
}
namespace test_framework {
template <>
struct SerializationTrait<Interval> : UserSerTrait<Interval, int, int> {
  static std::vector<std::string> GetMetricNames(const std::string& arg_name) {
    return {FmtStr("length({})", arg_name)};
  }

  static std::vector<int> GetMetrics(const Interval& x) {
    return {x.right - x.left};
  }
};
}  // namespace test_framework
bool operator==(const Interval& a, const Interval& b) {
  return a.left == b.left && a.right == b.right;
}

std::ostream& operator<<(std::ostream& out, const Interval& i) {
  return PrintTo(out, std::make_tuple(i.left, i.right));
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"disjoint_intervals", "new_interval"};
  return GenericTestMain(args, "interval_add.cc", "interval_add.tsv",
                         &AddInterval, DefaultComparator{}, param_names);
}
