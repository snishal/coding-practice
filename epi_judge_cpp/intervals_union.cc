#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
#include "test_framework/timed_executor.h"
using std::vector;

struct Interval {
  struct Endpoint {
    bool is_closed;
    int val;
  };

  Endpoint left, right;

  public:
  bool operator<(const Interval& i) const {
    if(left.val != i.left.val){
      return left.val < i.left.val;
    }
    return left.is_closed && !i.left.is_closed;
  }
};

vector<Interval> UnionOfIntervals(vector<Interval> intervals) {
  // TODO - you fill in here.
  if(intervals.empty()){
    return {};
  }

  std::sort(intervals.begin(), intervals.end());
  Interval curr(intervals.front());
  vector<Interval> res;
  for(int i = 1; i < intervals.size(); i++){
    if(intervals[i].left.val < curr.right.val || (intervals[i].left.val == curr.right.val && (intervals[i].left.is_closed || curr.right.is_closed))){
      if(intervals[i].right.val > curr.right.val || (intervals[i].right.val == curr.right.val && intervals[i].right.is_closed)){
        curr.right = intervals[i].right;
      }
    }else{
      res.emplace_back(curr);
      curr = intervals[i];
    }
  }
  res.emplace_back(curr);
  return res;
}
struct FlatInterval {
  int left_val;
  bool left_is_closed;
  int right_val;
  bool right_is_closed;

  FlatInterval(int left_val, bool left_is_closed, int right_val,
               bool right_is_closed)
      : left_val(left_val),
        left_is_closed(left_is_closed),
        right_val(right_val),
        right_is_closed(right_is_closed) {}

  explicit FlatInterval(Interval in)
      : left_val(in.left.val),
        left_is_closed(in.left.is_closed),
        right_val(in.right.val),
        right_is_closed(in.right.is_closed) {}

  operator Interval() const {
    return {{left_is_closed, left_val}, {right_is_closed, right_val}};
  }

  bool operator==(const FlatInterval& rhs) const {
    return std::tie(left_val, left_is_closed, right_val, right_is_closed) ==
           std::tie(rhs.left_val, rhs.left_is_closed, rhs.right_val,
                    rhs.right_is_closed);
  }
};

namespace test_framework {
template <>
struct SerializationTrait<FlatInterval>
    : UserSerTrait<FlatInterval, int, bool, int, bool> {};
}  // namespace test_framework

std::ostream& operator<<(std::ostream& out, const FlatInterval& i) {
  return out << (i.left_is_closed ? '<' : '(') << i.left_val << ", "
             << i.right_val << (i.right_is_closed ? '>' : ')');
}

std::vector<FlatInterval> UnionOfIntervalsWrapper(
    TimedExecutor& executor, const std::vector<FlatInterval>& intervals) {
  std::vector<Interval> casted;
  for (const FlatInterval& i : intervals) {
    casted.push_back(static_cast<Interval>(i));
  }

  std::vector<Interval> result =
      executor.Run([&] { return UnionOfIntervals(casted); });

  return {begin(result), end(result)};
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "intervals"};
  return GenericTestMain(args, "intervals_union.cc", "intervals_union.tsv",
                         &UnionOfIntervalsWrapper, DefaultComparator{},
                         param_names);
}
