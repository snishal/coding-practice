class Solution {
public:
    vector<int> grayCode(int n) {
        if(n == 0){
            return {0};
        }
        if(n == 1){
            return {0, 1};
        }
        
        auto grayCodesLessOne = grayCode(n - 1);
        int leading_bit_one = 1 << (n - 1);
        vector<int> reflection;
        
        for(int i = grayCodesLessOne.size() - 1; i >= 0; --i){
            reflection.emplace_back(leading_bit_one | grayCodesLessOne[i]);
        }
        vector<int> result = grayCodesLessOne;
        result.insert(result.end(), reflection.begin(), reflection.end());
        return result;
    }
};