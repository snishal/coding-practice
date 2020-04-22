#include <string>
#include <vector>

#include "test_framework/generic_test.h"
using std::string;
using std::vector;

int ComputeDistance(const string& A, int A_idx, const string& B, int B_idx,  vector<vector<int>>& dp){
  if(A_idx <  0){
    return B_idx + 1;
  }else if(B_idx < 0){
    return A_idx + 1;
  }

  if(dp[A_idx][B_idx] != -1){
    return dp[A_idx][B_idx];
  }
  if(A[A_idx] == B[B_idx]){
    dp[A_idx][B_idx] = ComputeDistance(A, A_idx - 1, B, B_idx - 1, dp);
  }else{
    dp[A_idx][B_idx] = 1 + std::min({
                    ComputeDistance(A, A_idx - 1, B, B_idx - 1, dp),
                    ComputeDistance(A, A_idx, B, B_idx - 1, dp),
                    ComputeDistance(A, A_idx - 1, B, B_idx, dp),
                  });
  }

  return dp[A_idx][B_idx];
}

int LevenshteinDistance(const string& A, const string& B) {
  vector<vector<int>> dp(A.size(), vector<int>(B.size(), -1));
  return ComputeDistance(A, A.size() - 1, B, B.size() - 1, dp);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "B"};
  return GenericTestMain(args, "levenshtein_distance.cc",
                         "levenshtein_distance.tsv", &LevenshteinDistance,
                         DefaultComparator{}, param_names);
}
