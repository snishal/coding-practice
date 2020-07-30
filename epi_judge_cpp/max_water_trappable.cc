#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

int CalculateTrappingWater(const vector<int>& heights) {
  // TODO - you fill in here.
  if(heights.empty()){
    return 0;
  }
  int max_h_idx = std::distance(heights.begin(), std::max_element(heights.begin(), heights.end()));

  int total_water_trapped = 0;

  int left_max_h = heights.front();
  for(int i = 1; i < max_h_idx; i++){
    if(heights[i] >= left_max_h){
      left_max_h = heights[i];
    }else{
      total_water_trapped += left_max_h - heights[i];
    }
  }

  int right_max_h = heights.back();
  for(int i = heights.size() - 2; i > max_h_idx; i--){
    if(heights[i] >= right_max_h){
      right_max_h = heights[i];
    }else{
      total_water_trapped += right_max_h - heights[i];
    }
  }

  return total_water_trapped;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"heights"};
  return GenericTestMain(args, "max_water_trappable.cc",
                         "max_water_trappable.tsv", &CalculateTrappingWater,
                         DefaultComparator{}, param_names);
}
