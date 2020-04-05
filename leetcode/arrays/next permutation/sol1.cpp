class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        
        int k = nums.size()-2;
        while(k >= 0 && nums[k+1] <= nums[k]){
            --k;
        }
        
        if(k == -1){
            reverse(nums.begin(), nums.end());
            return;
        }
        
        for(int i = nums.size() - 1; i > k; i--){
            if(nums[i] > nums[k]){
                swap(nums[i], nums[k]);
                break;
            }
        }
        
        reverse(nums.begin() + k + 1, nums.end());
        
    }
};