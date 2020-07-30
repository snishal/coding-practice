#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

bool MatrixSearch(const vector<vector<int>>& A, int x) {
  int r = 0, c = A.front().size() - 1;

  while(r < A.size() && c >= 0){
    if(A[r][c] == x){
      return true;
    }else if(A[r][c] < x){
      r++;
    }else {
      c--;
    }
  }

  return false;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "x"};
  return GenericTestMain(args, "search_row_col_sorted_matrix.cc",
                         "search_row_col_sorted_matrix.tsv", &MatrixSearch,
                         DefaultComparator{}, param_names);
}
