class Solution {
public:
    string multiply(string num1, string num2) {
        string result(num1.size() + num2.size(), 0);
        for(int i = num1.size() - 1; i >= 0; i--){
            for(int j = num2.size() - 1; j >= 0; j--){
                result[i + j + 1] += (num1[i] - '0') * (num2[j] - '0');
                result[i + j] += result[i + j + 1] / 10;
                result[i + j + 1] = result[i + j + 1] % 10;
            }
        }
        
        result = string(find_if_not(result.begin(), result.end(), [](char c){
            return !c;
        }), result.end());
        
        if(result.empty()){
            return "0";
        }
        
        for_each(result.begin(), result.end(), [](char& c){
           c += 48;
        });
        
        return result;
    }
};