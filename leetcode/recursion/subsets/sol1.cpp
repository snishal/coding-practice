class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> powerSet;
        for(int i = 0; i < (1 << nums.size()); i++){
            int bit_array = i;
            vector<int> subset = {};
            while(bit_array){
                subset.emplace_back(nums[log2(bit_array & ~(bit_array - 1))]);
                bit_array &= (bit_array - 1);
            }
            powerSet.emplace_back(subset);
        }
        
        return powerSet;
    }
};