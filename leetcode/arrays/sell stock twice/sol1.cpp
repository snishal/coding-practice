class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int min_price_so_far = numeric_limits<int>::max(), max_forward_profit = 0, max_profit = 0;
        
        for(int i = 0; i < prices.size() - 1; ++i){
            min_price_so_far = min(min_price_so_far, prices[i]);
            max_forward_profit = max(max_forward_profit, prices[i] - min_price_so_far);
        }
        
        int max_price_so_far = numeric_limits<int>::min();
        for(int i = prices.size() - 1; i > 0; i--){
            max_price_so_far = max(max_price_so_far, prices[i]);
            max_profit = max(max_profit, max_price_so_far - prices[i] + max_forward_profit);
            max_forward_profit = min(max_forward_profit, )
        }
        
        return max_profit;
    }
};