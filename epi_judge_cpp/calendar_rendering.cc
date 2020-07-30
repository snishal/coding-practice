#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
using std::vector;

struct Event {
  int start, finish;
};

struct EndPoint{
  bool operator< (const EndPoint& that) const{
    return (time != that.time ? time < that.time : isStart && !that.isStart);
  }
  bool isStart;
  int time;
};

int FindMaxSimultaneousEvents(const vector<Event>& A) {
  vector<EndPoint> E;
  for(const Event& e : A){
    E.push_back(EndPoint{true, e.start});
    E.push_back(EndPoint{false, e.finish});
  }

  std::sort(E.begin(), E.end(), std::less<EndPoint>());
  int max_events = 0, num_events = 0;

  for(const EndPoint& e : E){
    if(e.isStart){
      num_events++;
      max_events = std::max(max_events, num_events);
    }else{
      num_events--;
    }
  }

  return max_events;
}
namespace test_framework {
template <>
struct SerializationTrait<Event> : UserSerTrait<Event, int, int> {};
}  // namespace test_framework

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "calendar_rendering.cc",
                         "calendar_rendering.tsv", &FindMaxSimultaneousEvents,
                         DefaultComparator{}, param_names);
}
