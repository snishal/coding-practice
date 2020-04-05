class MedianFinder {
public:
    priority_queue<int, vector<int>, greater<int>>min_heap;
    priority_queue<int, vector<int>, less<int>>max_heap;
    
    /** initialize your data structure here. */
    MedianFinder() {
        
    }
    
    void addNum(int num) {
        if(min_heap.empty()){
            min_heap.push(num);
        }else{
            if(num >= min_heap.top()){
                min_heap.push(num);
            }else{
                max_heap.push(num);
            }
        }
        
        if(min_heap.size() > max_heap.size() + 1){
            max_heap.emplace(min_heap.top());
            min_heap.pop();
        }else if(max_heap.size() > min_heap.size()){
            min_heap.emplace(max_heap.top());
            max_heap.pop();
        }
    }
    
    double findMedian() {
        return (
                    min_heap.size() == max_heap.size()
                    ?
                    0.5 * (min_heap.top() + max_heap.top())
                    :
                    min_heap.top()
               );
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */