class Solution {
public:
    vector<int> grayCode(int n) {
        vector<int> result({0});
        directedGrayCode(n, new unordered_set<int>({0}), result);
        return result;
    }
    
    bool differByOneBit(int x, int y){
        int bit_diff = x ^ y;
        return bit_diff && !((bit_diff) & (bit_diff - 1));
    }
    
    bool directedGrayCode(int n, unordered_set<int>* generated, vector<int>& result){
        if(result.size() == 1 << n){
            return differByOneBit(result.front(), result.back());
        }
        
        for(int i = 0; i < n; i++){
            int prev_code = result.back();
            int candidate = prev_code ^ (1 << i);
            if(generated->find(candidate) == generated->end()){
                generated->emplace(candidate);
                result.emplace_back(candidate);
                if(directedGrayCode(n, generated, result)){
                    return true;
                }
                generated->erase(candidate);
                result.pop_back();
            }
        }
        
        return false;
    }
};