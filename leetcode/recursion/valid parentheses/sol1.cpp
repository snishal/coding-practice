class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> result;
        Generate(n, n, "", result);
        return result;
    }
    
private:
    void Generate(int left_needed, int right_needed, const string& valid_prefix, vector<string>& result){
        if(left_needed == 0 && right_needed == 0){
            result.emplace_back(valid_prefix);
        }
        
        if(left_needed > 0){
            Generate(left_needed - 1, right_needed, valid_prefix + "(", result);
        }
        if(right_needed > left_needed){
            Generate(left_needed, right_needed - 1, valid_prefix + ")", result);
        }
    }
};