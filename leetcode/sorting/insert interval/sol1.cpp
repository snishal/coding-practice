class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        vector<vector<int>> result;
        size_t i = 0;
        
        while(i < intervals.size() && intervals[i][1] < newInterval[0]){
            result.emplace_back(intervals[i]);
            i++;
        }
        
        while(i < intervals.size() && intervals[i][0] <= newInterval[1]){
            newInterval[0] = min(newInterval[0], intervals[i][0]);
            newInterval[1] = max(newInterval[1], intervals[i][1]);    
            i++;
        }
        
        result.emplace_back(newInterval);
        
        result.insert(result.end(), intervals.begin() + i, intervals.end());
        
        return result;
    }
};