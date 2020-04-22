#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
using std::stack;

int CalculateLargestRectangle(const vector<int>& heights) {
  stack<int> s;
  int max_area = 0;
  for(int i = 0; i <= heights.size(); i++){
      if(!s.empty() && i < heights.size() && heights[i] == heights[s.top()]){
          s.pop();
          s.push(i);
      }
      while(!s.empty() && (i == heights.size() || heights[i] < heights[s.top()])){
          int height = heights[s.top()];
          s.pop();
          int width = s.empty() ? i : i - s.top() - 1;
          max_area = std::max(max_area, height * width);
      }
      s.push(i);
  }
  
  return max_area;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"heights"};
  return GenericTestMain(args, "largest_rectangle_under_skyline.cc",
                         "largest_rectangle_under_skyline.tsv",
                         &CalculateLargestRectangle, DefaultComparator{},
                         param_names);
}
