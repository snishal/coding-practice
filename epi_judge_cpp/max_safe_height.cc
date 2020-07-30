#include "test_framework/generic_test.h"

#include <vector>
using std::vector;

int GetHeightMemoized(int cases, int drops, vector<vector<int>>& dp){
  if(cases == 0 || drops == 0){
    return 0;
  }else if(cases == 1){
    return drops;
  }else if(dp[cases][drops] == -1){
    dp[cases][drops] = GetHeightMemoized(cases, drops - 1, dp) + GetHeightMemoized(cases - 1, drops - 1, dp) + 1;
  }

  return dp[cases][drops];
}

int GetHeight(int cases, int drops) {
  // TODO - you fill in here.
  vector<vector<int>> dp(cases + 1, vector<int>(drops + 1, -1));
  return GetHeightMemoized(cases, drops, dp);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"cases", "drops"};
  return GenericTestMain(args, "max_safe_height.cc", "max_safe_height.tsv",
                         &GetHeight, DefaultComparator{}, param_names);
}
