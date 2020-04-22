#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

int GetMaxTrappedWater(const vector<int>& heights) {
  int i = 0, j = heights.size() - 1;
  int max_trapped_water = std::numeric_limits<int>::min();
  while(i < j){
    max_trapped_water = std::max(max_trapped_water, std::min(heights[i], heights[j]) * (j - i));
    if(heights[i] == heights[j]){
      ++i, --j;
    }else if(heights[i] < heights[j]){
      ++i;
    }else{
      --j;
    }
  }
  return max_trapped_water;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"heights"};
  return GenericTestMain(args, "max_trapped_water.cc", "max_trapped_water.tsv",
                         &GetMaxTrappedWater, DefaultComparator{}, param_names);
}
