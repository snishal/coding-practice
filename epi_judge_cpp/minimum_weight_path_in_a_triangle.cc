#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
// Solution 1
int MinimumPathWeight(const vector<vector<int>>& triangle) {
  if(triangle.empty()){
    return 0;
  }
  vector<int> prevPathWeight(triangle.front());
  for(int i = 1; i < triangle.size(); i++){
    vector<int> currPathWeight(triangle[i]);
    currPathWeight.front() += prevPathWeight.front();
    for(int j = 1; j < triangle[i].size() - 1; j++){
      currPathWeight[j] += std::min(prevPathWeight[j-1], prevPathWeight[j]);
    }
    currPathWeight.back() += prevPathWeight.back();
    prevPathWeight.swap(currPathWeight);
  }

  return *std::min_element(prevPathWeight.begin(), prevPathWeight.end());
}

// Solution 2
// int MinimumPathWeight(const vector<vector<int>>& triangle) {
//   if(triangle.empty()){
//     return 0;
//   }
//   vector<int> pathWeight(triangle.back());
//   for(int i = triangle.size() - 2; i >= 0; i--){
//     for(int j = 0; j < triangle[i].size(); j++){
//       pathWeight[j] = std::min(pathWeight[j], pathWeight[j + 1]) + triangle[i][j];
//     }
//     pathWeight.pop_back();
//   }

//   return pathWeight.front();
// }

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"triangle"};
  return GenericTestMain(args, "minimum_weight_path_in_a_triangle.cc",
                         "minimum_weight_path_in_a_triangle.tsv",
                         &MinimumPathWeight, DefaultComparator{}, param_names);
}
