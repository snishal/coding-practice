class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if(nums.empty()){
            return 0;
        }
        
        int write_index = 1;
        for(int i = 1; i < nums.size(); i++){
            if(nums[write_index - 1] != nums[i]){
                nums[write_index++] = nums[i];
            }
        }
        
        return write_index;
    }
};