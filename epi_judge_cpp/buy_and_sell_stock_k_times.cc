#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

// Time : O(kn^2) Space : O(kn)
// double BuyAndSellStockKTimes(const vector<double>& prices, int k) {
//   vector<vector<double>> dp(k + 1, vector<double>(prices.size(), 0));

//   for(int num_stocks = 1; num_stocks <= k; num_stocks++){
//     for(int sell_stock = 1; sell_stock < prices.size(); sell_stock++){
//       double max_profit = 0;
//       for(int buy_stock = 0; buy_stock < sell_stock; buy_stock++){
//         max_profit = std::max(max_profit, prices[sell_stock] - prices[buy_stock] + dp[num_stocks - 1][buy_stock]);
//       }
//       dp[num_stocks][sell_stock] = std::max(dp[num_stocks][sell_stock - 1], max_profit);
//     }
//   }

//   return dp.back().back();
// }
double BuyAndSellStockKTimes(const vector<double>& prices, int k) {
  vector<double> dp(2 * k, std::numeric_limits<double>::lowest());

  for(int stock = 0; stock < prices.size(); stock++){
    vector<double> prev(dp);
    for(int j = 0, sign = -1; j < dp.size() && j <= stock; j++, sign *= -1){
      double purchasing_power = prices[stock]*sign + (j == 0 ? 0 : prev[j - 1]);
      dp[j] = std::max(prev[j], purchasing_power);
    }
  }

  return dp.back();
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"prices", "k"};
  return GenericTestMain(
      args, "buy_and_sell_stock_k_times.cc", "buy_and_sell_stock_k_times.tsv",
      &BuyAndSellStockKTimes, DefaultComparator{}, param_names);
}
