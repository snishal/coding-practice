// Solution 1
class Solution {
public:
    int findMaxLength(vector<int>& nums) {
        vector<int> A(2 * nums.size() + 1, -2);
        A[nums.size()] = -1;
        int count = 0, maxLen = 0;
        for(int i = 0; i < nums.size(); i++){
            count += (nums[i] == 0) ? -1 : 1;
            if(A[count + nums.size()] >= -1){
                maxLen = max(maxLen, i - A[count + nums.size()]);
            }else{
                A[count + nums.size()] = i;
            }
        }
        
        return maxLen;
    }
};

// Solution 2
class Solution {
public:
    int findMaxLength(vector<int>& nums) {
        unordered_map<int, int> A;
        A[0] = -1;
        int count = 0, maxLen = 0;
        for(int i = 0; i < nums.size(); i++){
            count += (nums[i] == 0) ? -1 : 1;
            if(A.find(count) != A.end()){
                maxLen = max(maxLen, i - A[count]);
            }else{
                A[count] = i;
            }
        }
        
        return maxLen;
    }
};