#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

// Solution 1
// Space Complexity is O(n * s);
// int NumCombinationsForFinalScore(int final_score,
//                                  const vector<int>& individual_play_scores) {
  
//   vector<vector<int>> dp(individual_play_scores.size(), vector<int>(final_score + 1, 0));
//   for(int i = 0; i < individual_play_scores.size(); i++){
//     dp[i][0] = 1;
//     for(int j = 1; j <= final_score; j++){
//       int with_this = (j >= individual_play_scores[i]) ? dp[i][j - individual_play_scores[i]] : 0;
//       int without_this = (i > 0) ? dp[i - 1][j] : 0;
//       dp[i][j] = with_this + without_this;
//     }
//   }

//   return dp[individual_play_scores.size() - 1][final_score];
// }

// Solution 2
// Space Complexity is O(n)
int NumCombinationsForFinalScore(int final_score,
                                 const vector<int>& individual_play_scores) {
  
  vector<int> dp(final_score + 1, 0);
  dp[0] = 1;
  
  for(int i = 0; i < individual_play_scores.size(); i++){
    for(int j = individual_play_scores[i]; j <= final_score; j++){
      dp[j] += dp[j - individual_play_scores[i]];
    }
  }

  return dp[final_score];
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"final_score", "individual_play_scores"};
  return GenericTestMain(args, "number_of_score_combinations.cc",
                         "number_of_score_combinations.tsv",
                         &NumCombinationsForFinalScore, DefaultComparator{},
                         param_names);
}
