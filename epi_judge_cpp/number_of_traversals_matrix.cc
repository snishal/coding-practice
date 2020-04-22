#include "test_framework/generic_test.h"

#include <vector>
using std::vector;

// Solution 1 
// int NumberOfWays(int n, int m) {
//   vector<vector<int>> dp(n, vector<int>(m , 0));
//   dp[0][0] = 1;

//   for(int i = 0; i < n; i++){
//     for(int j = 0; j < m; j++){
//       dp[i][j] += (i > 0) ? dp[i - 1][j] : 0;
//       dp[i][j] += (j > 0) ? dp[i][j - 1] : 0;
//     }
//   }

//   return dp[n - 1][m - 1];
// }

// Solution 2
int NumberOfWays(int n, int m) {
  vector<int> dp(std::min(n, m), 0);
  dp[0] = 1;

  for(int i = 0; i < std::max(n, m); i++){
    for(int j = 1; j < std::min(n, m); j++){
      dp[j] += dp[j - 1];
    }
  }

  return dp.back();
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n", "m"};
  return GenericTestMain(args, "number_of_traversals_matrix.cc",
                         "number_of_traversals_matrix.tsv", &NumberOfWays,
                         DefaultComparator{}, param_names);
}
