//Solution 1
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int max_so_far = 0, max_ending_here = 0;
        bool allNegative = true;
        
        for(const int& num : nums){
            max_ending_here += num;
            
            if(max_ending_here < 0){
                max_ending_here = 0;
            }
            
            if(max_ending_here > max_so_far){
                max_so_far = max_ending_here;
                allNegative = false;
            }
        }
        
        return (allNegative) ? *max_element(nums.begin(), nums.end()) : max_so_far;
    }
};

// Solution 2
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        return helperMaxSum(nums, 0, nums.size() - 1);
    }
    
    int maxSumIncludeMid(vector<int>& nums, int l, int m, int r){
        int leftSum = INT_MIN, rightSum = INT_MIN, sum = 0;
        
        sum = 0;
        for(int i = m; i >= l; i--){
            sum += nums[i];
            leftSum = max(leftSum, sum);
        }
        
        sum = 0;
        for(int i = m+1; i <= r; i++){
            sum += nums[i];
            rightSum = max(rightSum, sum);
        }
        
        return leftSum + rightSum;
    }
    
    int helperMaxSum(vector<int>& nums, int l, int r){
        if(l == r){
            return nums[l];
        }else if(l < r){
            int m = (l + r)/2;
            return max({helperMaxSum(nums, l, m), helperMaxSum(nums, m+1, r), maxSumIncludeMid(nums, l , m , r)});
        }
        return INT_MIN;
    }
};