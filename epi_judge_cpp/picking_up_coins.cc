#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

// Solution 1
// int MaximumRevenueFor(const vector<int>& coins, int i, int j, vector<vector<int>>& revenue){
//   if(i > j){
//     return 0;
//   }
//   if(revenue[i][j] == 0){
//     revenue[i][j] = std::max(
//                       coins[i] + std::min(MaximumRevenueFor(coins, i + 2, j, revenue), MaximumRevenueFor(coins, i + 1, j - 1, revenue)),
//                       coins[j] + std::min(MaximumRevenueFor(coins, i, j - 2, revenue), MaximumRevenueFor(coins, i + 1, j - 1, revenue))
//                     );
//   }
//   return revenue[i][j];
// }

// int MaximumRevenue(const vector<int>& coins) {
//   vector<vector<int>> revenue(coins.size(), vector<int>(coins.size(), 0));
//   return MaximumRevenueFor(coins, 0, coins.size() - 1, revenue);
// }

// Solution2
int MaximumRevenue(const vector<int>& coins) {
  vector<vector<int>> revenue(coins.size(), vector<int>(coins.size(), 0));
  for (int i = 0; i < coins.size(); i++){
    revenue[i][i] = coins[i];
  }
  
  for(int i = 1; i < coins.size(); i++){
    for(int j = i; j < coins.size(); j++){
      int x = (j - i + 2 <= j) ? revenue[j - i + 2][j] : 0;
      int y = (j - i + 1 <= j - 1) ? revenue[j - i + 1][j - 1] : 0;
      int z = (j - i <= j - 2) ? revenue[j - i][j - 2] : 0;
      revenue[j - i][j] = std::max(
                            coins[j - i] + std::min(x, y),
                            coins[j] + std::min(y, z)
                          ); 
    }
  }
  return revenue.front().back();
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"coins"};
  return GenericTestMain(args, "picking_up_coins.cc", "picking_up_coins.tsv",
                         &MaximumRevenue, DefaultComparator{}, param_names);
}
