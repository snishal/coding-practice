class Solution {
public:
    
    int util(vector<int>& nums, int l, int r,  int target){
        
        if(l > r){
            return -1;
        }
        else{
            int m = (l + r)/2;

            if(nums[m] == target){
                return m;
            }else if(nums[l] <= nums[m]){
                if(nums[l] <= target && target < nums[m])
                    return util(nums, l, m-1, target);
                else
                    return util(nums, m+1, r, target);
            }else{
                if(nums[m] < target && target <= nums[r])
                    return util(nums, m+1, r, target);
                else
                    return util(nums, l, m-1, target);
            }
        }
        
    }
    
    int search(vector<int>& nums, int target) {
        
        return util(nums, 0, nums.size()-1, target);
        
    }
};