class Solution {
public:
    void sortColors(vector<int>& nums) {
        int smaller = 0, equal = 0, larger = nums.size();
        int pivot = 1;
        
        while(equal < larger){
            if(nums[equal] < pivot){
                swap(nums[equal++], nums[smaller++]);
            }else if(nums[equal] == pivot){
                equal++;
            }else{
                swap(nums[equal], nums[--larger]);
            }
        }
    }
};