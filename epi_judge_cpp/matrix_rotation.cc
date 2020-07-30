#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
void RotateMatrix(vector<vector<int>>* square_matrix_ptr) {
  vector<vector<int>>& square_matrix = *square_matrix_ptr;
  int n = square_matrix.size();

  for(int i = 0; i < n / 2; i++){
    for(int j = i; j < n - i - 1; j++){
      int a = square_matrix[i][j];
      int b = square_matrix[j][n - i - 1];
      int c = square_matrix[n - i - 1][n - j - 1];
      int d = square_matrix[n - j - 1][i];

      square_matrix[i][j] = d;
      square_matrix[j][n - i - 1] = a;
      square_matrix[n - i - 1][n - j - 1] = b;
      square_matrix[n - j - 1][i] = c;
    }
  }

  return;
}
vector<vector<int>> RotateMatrixWrapper(vector<vector<int>> square_matrix) {
  RotateMatrix(&square_matrix);
  return square_matrix;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"square_matrix"};
  return GenericTestMain(args, "matrix_rotation.cc", "matrix_rotation.tsv",
                         &RotateMatrixWrapper, DefaultComparator{},
                         param_names);
}
