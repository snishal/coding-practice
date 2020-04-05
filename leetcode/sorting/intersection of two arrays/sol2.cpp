class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        unordered_set s(nums1.begin(), nums1.end());
        vector<int> intersection;
        
        for(int v : nums2){
            if(s.find(v) != s.end()){
                intersection.emplace_back(v);
                s.erase(v);
            }
        }
        
        return intersection;
    }
};