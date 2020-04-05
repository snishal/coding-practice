class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int i = m-1, j = n-1, write_idx = m + n - 1;
        
        while(i >= 0 && j >= 0){
            nums1[write_idx--] = nums1[i] > nums2[j] ? nums1[i--] : nums2[j--];
        }
        
        while(j >= 0){
            nums1[write_idx--] = nums2[j--];
        }
    }
};