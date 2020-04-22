#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

bool find(const vector<vector<int>>& grid, int r, int c, const vector<int>& pattern, int offset){
  if(offset == pattern.size()){
    return true;
  }
  if(r < 0 || r >= grid.size() || c < 0 || c >= grid[r].size() || grid[r][c] != pattern[offset]){
    return false;
  }

  bool found = find(grid, r - 1, c, pattern, offset + 1) || 
               find(grid, r + 1, c, pattern, offset + 1) || 
               find(grid, r, c - 1, pattern, offset + 1) || 
               find(grid, r, c + 1, pattern, offset + 1);

  return found;
}

bool IsPatternContainedInGrid(const vector<vector<int>>& grid,
                              const vector<int>& pattern) {
  for(int r = 0; r < grid.size(); r++){
    for(int c = 0; c < grid[r].size(); c++){
      if(find(grid, r, c, pattern, 0)){
        return true;
      }
    }
  }
  return false;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"grid", "pattern"};
  return GenericTestMain(args, "is_string_in_matrix.cc",
                         "is_string_in_matrix.tsv", &IsPatternContainedInGrid,
                         DefaultComparator{}, param_names);
}
