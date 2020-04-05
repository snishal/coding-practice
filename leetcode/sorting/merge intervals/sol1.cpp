class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        vector<vector<int>> result;
        
        if(intervals.size() > 0){
            auto cmp = [](const vector<int>& i1, const vector<int>& i2){
                return (i1[0] == i2[0]) ? i1[1] < i2[1] : i1[0] < i2[0];
            };

            sort(intervals.begin(), intervals.end(), cmp);

            result.emplace_back(intervals[0]);
            for(int i = 1; i < intervals.size(); i++){
                if(intervals[i][0] <= result.back()[1]){
                    result.back()[1] = max(result.back()[1], intervals[i][1]);
                }else{
                    result.emplace_back(intervals[i]);
                }
            }
        }
        
        return result;
    }
};