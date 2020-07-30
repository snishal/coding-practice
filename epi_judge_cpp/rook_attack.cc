#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

void RookAttack(vector<vector<int>>* A_ptr) {
  vector<vector<int>>& A = *A_ptr;
  int m = A.size(), n = A[0].size();
  bool row_has_zero = false, col_has_zero = false;

  for(int c = 0; c < n; c++){
    if(!A[0][c]){
      row_has_zero = true;
      break;
    }
  }

  for(int r = 0; r < m; r++){
    if(!A[r][0]){
      col_has_zero = true;
      break;
    }
  }

  for(int r = 1; r < m; r++){
    for(int c = 1; c < n; c++){
      if(!A[r][c]){
        A[r][0] = A[0][c] = 0;
      }
    }
  }

  for(int r = 1; r < m; r++){
    if(!A[r][0]){
      for(int c = 1; c < n; c++){
        A[r][c] = 0;
      }
    }
  }

  for(int c = 1; c < n; c++){
    if(!A[0][c]){
      for(int r = 1; r < m; r++){
        A[r][c] = 0;
      }
    }
  }

  if(row_has_zero){
    for(int c = 0; c < n; c++){
      A[0][c] = 0;
    }
  }

  if(col_has_zero){
    for(int r = 0; r < m; r++){
      A[r][0] = 0;
    }
  }
}
vector<vector<int>> RookAttackWrapper(vector<vector<int>> A) {
  vector<vector<int>> a_copy = A;
  RookAttack(&a_copy);
  return a_copy;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "rook_attack.cc", "rook_attack.tsv",
                         &RookAttackWrapper, DefaultComparator{}, param_names);
}
