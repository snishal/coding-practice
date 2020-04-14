class Solution {
public:
    int lastStoneWeight(vector<int>& stones) {
        priority_queue<int, vector<int>, less<int>> max_heap(stones.begin(), stones.end());
        
        int y, x;
        while(max_heap.size() > 1){
            y = max_heap.top();
            max_heap.pop();
            x = max_heap.top();
            max_heap.pop();
            
            y = y - x;
            max_heap.push(y);
        }
        
        if(!max_heap.empty())return max_heap.top();
        
        return 0;
    }
};