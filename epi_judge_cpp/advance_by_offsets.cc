#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
bool CanReachEnd(const vector<int>& max_advance_steps) {
  int max_reach = 0;

  for(int i = 0; i < max_advance_steps.size() && i <= max_reach; i++){
    max_reach = std::max(max_reach, i + max_advance_steps[i]);
  }
  
  return max_reach >= max_advance_steps.size() - 1;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"max_advance_steps"};
  return GenericTestMain(args, "advance_by_offsets.cc",
                         "advance_by_offsets.tsv", &CanReachEnd,
                         DefaultComparator{}, param_names);
}
