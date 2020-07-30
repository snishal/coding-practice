#include <vector>
#include <unordered_set>
#include <utility>

#include "test_framework/generic_test.h"
using std::vector;
using std::unordered_set;
using std::pair;

// void SpiralOrdering(const vector<vector<int>>& square_matrix, int i, vector<int>& spiral_order){
//   int n = square_matrix.size();

//   if(i == n - i - 1){
//     spiral_order.emplace_back(square_matrix[i][i]);
//     return;
//   }
//   for(int j = i; j < n - i - 1; j++){
//     spiral_order.emplace_back(square_matrix[i][j]);
//   }

//   for(int j = i; j < n - i - 1; j++){
//     spiral_order.emplace_back(square_matrix[j][n - i - 1]);
//   }

//   for(int j = n - i - 1; j > i; j--){
//     spiral_order.emplace_back(square_matrix[n - i- 1][j]);
//   }

//   for(int j = n - i - 1; j > i; j--){
//     spiral_order.emplace_back(square_matrix[j][i]);
//   }
// }

// vector<int> MatrixInSpiralOrder(const vector<vector<int>>& square_matrix) {
//   int n = square_matrix.size();

//   vector<int> spiral_order;
//   for(int i = 0; i < std::ceil(0.5 * n); i++){
//     SpiralOrdering(square_matrix, i, spiral_order);
//   }

//   return spiral_order;
// }

vector<int> MatrixInSpiralOrder(const vector<vector<int>>& square_matrix) {
  int n = square_matrix.size();
  const vector<vector<int>> move = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

  vector<int> spiral_order;

  struct HashPair{
    size_t operator()(const pair<int, int> p) const {
      return std::hash<int>()(p.first) << 31 ^ std::hash<int>()(p.second); 
    }
  };
  unordered_set<pair<int, int>, HashPair> visited;

  int r = 0, c = 0, dir = 0;
  for(int i = 0; i < n * n; i++){
    spiral_order.emplace_back(square_matrix[r][c]);
    visited.emplace(r, c);
    int next_r = r + move[dir][0], next_c = c + move[dir][1];
    if(next_r < 0 || next_r >= n || next_c < 0 || next_c >= n || visited.count({next_r, next_c})){
      dir = (dir + 1) % 4;
      next_r = r + move[dir][0], next_c = c + move[dir][1];
    }
    r = next_r, c = next_c;
  }

  return spiral_order;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"square_matrix"};
  return GenericTestMain(args, "spiral_ordering.cc", "spiral_ordering.tsv",
                         &MatrixInSpiralOrder, DefaultComparator{},
                         param_names);
}
