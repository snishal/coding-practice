class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<int> resProd(nums.size(), 1);
        
        int leftCummProd = 1;
        for(int i = 0; i < nums.size(); i++){
            resProd[i] *= leftCummProd;
            leftCummProd *= nums[i];
        }
        
        int rightCummProd = 1;
        for(int i = nums.size() - 1; i >= 0; i--){
            resProd[i] *= rightCummProd;
            rightCummProd *= nums[i];
        }
        
        return resProd;
    }
};