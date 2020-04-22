#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
using std::vector;

struct Item {
  int weight, value;
};

// Solution 1
// int Opt(const vector<Item>& items, int k, int available_capacity, vector<vector<int>>& dp){
//   if(k < 0){
//     return 0;
//   }
//   if(dp[k][available_capacity] == -1){
//     int without_k = Opt(items, k - 1, available_capacity, dp);
//     int with_k = (available_capacity < items[k].weight) ? 0 : Opt(items, k - 1, available_capacity - items[k].weight, dp) + items[k].value;
//     dp[k][available_capacity] = std::max(without_k, with_k);
//   }
//   return dp[k][available_capacity];
// }

// int OptimumSubjectToCapacity(const vector<Item>& items, int capacity) {
//   vector<vector<int>> dp(items.size(), vector<int>(capacity + 1, -1));
//   return Opt(items, items.size() - 1, capacity, dp);
// }

// Solution 2
// int OptimumSubjectToCapacity(const vector<Item>& items, int capacity) {
//   vector<vector<int>> dp(items.size(), vector<int>(capacity + 1, 0));
//   for(int i = 0; i < items.size(); i++){
//     for(int j = 1; j <= capacity; j++){
//       int without_i = (i > 0) ? dp[i - 1][j] : 0;
//       int with_i = (j < items[i].weight) ? 0 : ( (i > 0) ? dp[i - 1][j - items[i].weight] : 0 ) + items[i].value;
//       dp[i][j] = std::max(without_i, with_i);
//     }
//   }

//   return dp[items.size() - 1][capacity];
// }

// Solution 3
int OptimumSubjectToCapacity(const vector<Item>& items, int capacity) {
  vector<int> dp(capacity + 1, 0);
  for(int i = 0; i < items.size(); i++){
    for(int j = capacity; j >= items[i].weight; j--){
      dp[j] = std::max(dp[j], dp[j - items[i].weight] + items[i].value);
    }
  }

  return dp[capacity];
}

namespace test_framework {
template <>
struct SerializationTrait<Item> : UserSerTrait<Item, int, int> {};
}  // namespace test_framework

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"items", "capacity"};
  return GenericTestMain(args, "knapsack.cc", "knapsack.tsv",
                         &OptimumSubjectToCapacity, DefaultComparator{},
                         param_names);
}
