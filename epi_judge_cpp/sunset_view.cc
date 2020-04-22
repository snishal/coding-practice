#include <iterator>
#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
vector<int> ExamineBuildingsWithSunset(
    vector<int>::const_iterator sequence_begin,
    const vector<int>::const_iterator& sequence_end) {
      int idx = 0;
      std::stack<std::pair<int, int>> s;
      for(auto itr = sequence_begin; itr != sequence_end; itr = std::next(itr)){
        while(!s.empty() && s.top().second <= *(itr)){
          s.pop();
        }
        s.emplace(idx++, *(itr));
      }

      std::vector<int> buildingHeights;

      while(!s.empty()){
        buildingHeights.emplace_back(s.top().first);
        s.pop();
      }

      return buildingHeights;
}
vector<int> ExamineBuildingsWithSunsetWrapper(const vector<int>& sequence) {
  return ExamineBuildingsWithSunset(cbegin(sequence), cend(sequence));
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"sequence"};
  return GenericTestMain(args, "sunset_view.cc", "sunset_view.tsv",
                         &ExamineBuildingsWithSunsetWrapper,
                         DefaultComparator{}, param_names);
}
