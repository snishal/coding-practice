class Solution {
public:
    bool canJump(vector<int>& nums) {
        int farthest_reach_so_far = 0, last_index = nums.size() - 1;
        for(int i = 0; i <= farthest_reach_so_far && farthest_reach_so_far < last_index; i++){
            farthest_reach_so_far = max(farthest_reach_so_far, i + nums[i]);
        }
        
        return farthest_reach_so_far >= last_index;
    }
};