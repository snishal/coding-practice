#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
double BuyAndSellStockTwice(const vector<double>& prices) {
  vector<double> forward_profits(prices.size(), 0);
  double prev_min = std::numeric_limits<double>::max(), max_profit = 0.0;
  for(int i = 0; i < prices.size(); i++){
    prev_min = std::min(prev_min, prices[i]);
    max_profit = std::max(max_profit, prices[i] - prev_min);
    forward_profits[i] = max_profit;
  }

  double next_max = std::numeric_limits<double>::min(), max_profit_two_stocks = 0.0;
  for(int i = prices.size() - 1; i > 0; i--){
    next_max = std::max(next_max, prices[i]);
    max_profit_two_stocks = std::max(max_profit_two_stocks, next_max - prices[i] + forward_profits[i]);
  }

  return max_profit_two_stocks;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"prices"};
  return GenericTestMain(args, "buy_and_sell_stock_twice.cc",
                         "buy_and_sell_stock_twice.tsv", &BuyAndSellStockTwice,
                         DefaultComparator{}, param_names);
}
