#include <algorithm>
#include <iterator>
#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

bool IsValid(vector<int>& col_placements){
  int row = col_placements.size() - 1;
  for(int i = 0; i < row; i++){
    int diff = std::abs(col_placements[i] - col_placements[row]);
    if(diff == 0 || diff == row - i){
      return false;
    }
  }
  return true;
}

void Helper(int n, int row, vector<int>& col_placement,  vector<vector<int>>& placements){
  if(n == row){
    placements.emplace_back(col_placement);
    return;
  }

  for(int col = 0; col < n; col++){
    col_placement.emplace_back(col);
    if(IsValid(col_placement)){
      Helper(n, row + 1, col_placement, placements);
    }
    col_placement.pop_back();
  }
}

vector<vector<int>> NQueens(int n) {
  vector<int> col_placement;
  vector<vector<int>> placements;
  Helper(n, 0, col_placement, placements);

  return placements;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n"};
  return GenericTestMain(args, "n_queens.cc", "n_queens.tsv", &NQueens,
                         UnorderedComparator{}, param_names);
}
