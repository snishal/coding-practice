class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int K) {
        auto cmp = [](const vector<int>& p1, const vector<int>& p2){
            return p1[0]*p1[0] + p1[1]*p1[1] < p2[0]*p2[0] + p2[1]*p2[1];    
        };
        
        priority_queue<vector<int>, vector<vector<int>>, decltype(cmp)> max_heap(cmp);
        
        for(const auto &point : points){
            max_heap.push(point);
            if(max_heap.size() > K)max_heap.pop();
        }
        
        vector<vector<int>> closest;
        while(!max_heap.empty()){
            closest.emplace_back(max_heap.top());
            max_heap.pop();
        }
        
        return closest;
    }
};