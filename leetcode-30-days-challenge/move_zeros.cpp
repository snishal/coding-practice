class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int write_index = -1;
        
        for(int i = 0; i < nums.size(); i++){
            if(nums[i] != 0){
                swap(nums[++write_index], nums[i]);
            }   
        }
    }
};