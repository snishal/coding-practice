class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        
        int i = nums.size()-2, j;
        while(i >= 0 && nums[i+1] <= nums[i])i--;
        
        if(i >= 0){
            j = nums.size()-1;
            while(j > i+1 && nums[j] <= nums[i])j--;
        
            swap(nums[i], nums[j]);
        }
        
        for(int k = 0; k < ((nums.size()-i-1)/2); k++){
            swap(nums[k+i+1], nums[nums.size()-1-k]);
        }
        
    }
};