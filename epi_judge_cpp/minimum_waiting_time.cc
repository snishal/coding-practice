#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

int MinimumTotalWaitingTime(vector<int> service_times) {
  sort(service_times.begin(), service_times.end());
  int total_waiting_time = 0;
  int total_queries = service_times.size();

  for(int i = 0; i < total_queries; i++){
    total_waiting_time += service_times[i] * (total_queries - i - 1);
  }
  return total_waiting_time;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"service_times"};
  return GenericTestMain(args, "minimum_waiting_time.cc",
                         "minimum_waiting_time.tsv", &MinimumTotalWaitingTime,
                         DefaultComparator{}, param_names);
}
