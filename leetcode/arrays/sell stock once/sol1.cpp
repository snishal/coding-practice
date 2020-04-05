class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int min_price_so_far = numeric_limits<int>::max(), max_profit = 0;
        for(const int& price : prices){
            max_profit = max(max_profit, price - min_price_so_far);
            min_price_so_far = min(min_price_so_far, price);
        }
        
        return max_profit;
    }
};