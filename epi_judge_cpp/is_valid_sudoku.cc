#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

bool HasDuplicate(const vector<vector<int>>& partial_assignment, int r, int re, int c, int ce){
  vector<bool> present(partial_assignment.size() + 1, false);

  for(int i = r; i < re; i++){
    for(int j = c; j < ce; j++){
      if(partial_assignment[i][j] != 0 && present[partial_assignment[i][j]]){
        return true;
      }
      present[partial_assignment[i][j]] = true;
    }
  }

  return false;
}

// Check if a partially filled matrix has any conflicts.
bool IsValidSudoku(const vector<vector<int>>& partial_assignment) {
  int m = partial_assignment.size(), n = partial_assignment.front().size();
  
  for(int i = 0; i < m; i++){
    if(HasDuplicate(partial_assignment, i, i + 1, 0, n)){
      return false;
    }
  }

  for(int i = 0; i < n; i++){
    if(HasDuplicate(partial_assignment, 0, m, i, i + 1)){
      return false;
    }
  }


  int I = std::sqrt(m), J = std::sqrt(n);
  for(int i = 0; i < I; i++){
    for(int j = 0; j < J; j++){
      if(HasDuplicate(partial_assignment, i * I, (i + 1) * I, j * J, (j + 1) * J)){
        return false;
      }
    }
  }

  return true;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"partial_assignment"};
  return GenericTestMain(args, "is_valid_sudoku.cc", "is_valid_sudoku.tsv",
                         &IsValidSudoku, DefaultComparator{}, param_names);
}
