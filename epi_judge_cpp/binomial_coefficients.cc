#include "test_framework/generic_test.h"

using std::vector;

int nCk(int n, int k, vector<vector<int>>& dp){
  if(k == 0 || n == k){
    return 1;
  }
  if(dp[n][k] == 0){
    dp[n][k] = nCk(n - 1, k, dp) + nCk(n - 1, k - 1, dp);
  }
  return dp[n][k];
}

int ComputeBinomialCoefficient(int n, int k) {
  vector<vector<int>> dp(n + 1, vector<int>(k + 1, 0));
  return nCk(n, k, dp);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n", "k"};
  return GenericTestMain(
      args, "binomial_coefficients.cc", "binomial_coefficients.tsv",
      &ComputeBinomialCoefficient, DefaultComparator{}, param_names);
}
