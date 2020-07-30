#include <vector>
#include <deque>

#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
using std::vector;
using std::deque;

struct TrafficElement {
  bool operator==(const TrafficElement& that) const {
    return time == that.time && volume == that.volume;
  }

  int time;
  double volume;
};
vector<TrafficElement> CalculateTrafficVolumes(const vector<TrafficElement>& A,
                                               int w) {
  deque<TrafficElement> window;
  vector<TrafficElement> maximum_volumes;

  for(const auto& trafficElement : A){
    while(!window.empty() && (trafficElement.time - window.front().time > w)){
      window.pop_front();
    }
    while(!window.empty() && (trafficElement.volume >= window.back().volume)){
      window.pop_back();
    }
    window.emplace_back(trafficElement);
    maximum_volumes.emplace_back(TrafficElement{trafficElement.time, window.front().volume});
  }

  return maximum_volumes;
}

namespace test_framework {
template <>
struct SerializationTrait<TrafficElement>
    : UserSerTrait<TrafficElement, int, double> {};
}  // namespace test_framework

std::ostream& operator<<(std::ostream& out, const TrafficElement& te) {
  return out << '[' << te.time << ", " << te.volume << ']';
};

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "w"};
  return GenericTestMain(args, "max_of_sliding_window.cc",
                         "max_of_sliding_window.tsv", &CalculateTrafficVolumes,
                         DefaultComparator{}, param_names);
}
