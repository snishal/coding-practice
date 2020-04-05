class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        bool carry = false;;
        int r = digits.size() - 1;
        
        digits[r] += 1;
        carry = digits[r] / 10;
        digits[r] %= 10;
        
        for(int i = r - 1; (i >= 0 && carry); i--){
            digits[i] += 1;
            carry = digits[i] / 10;
            digits[i] %= 10;
        }
        
        if(carry)digits.insert(digits.begin(), 1);
        
        return digits;
    }
};