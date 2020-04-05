class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        vector<int> intersection;
        
        sort(nums1.begin(), nums1.end());
        sort(nums2.begin(), nums2.end());
        
        int i = 0, j = 0;
        
        while(i < nums1.size() && j < nums2.size()){
            if(nums1[i] == nums2[j]){
                intersection.emplace_back(nums1[i]);
                i++;
                j++;
                while(i < nums1.size() && nums1[i] == nums1[i-1])i++;
                while(j < nums2.size() && nums2[j] == nums2[j-1])j++;
            }else if(nums1[i] < nums2[j]){
                i++;
            }else{
                j++;
            }
        }
        
        return intersection;
    }
};