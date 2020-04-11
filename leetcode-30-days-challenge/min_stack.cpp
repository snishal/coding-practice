class MinStack {
public:
    /** initialize your data structure here. */
    
    stack<int> s;
    stack<int> aux;
    
    MinStack() {
        
    }
    
    void push(int x) {
        s.push(x);
        if(aux.empty() || x <= aux.top()){
            aux.push(x);
        }
    }
    
    void pop() {
        if(s.top() == aux.top()){
            aux.pop();
        }
        s.pop();
    }
    
    int top() {
        return s.top();
    }
    
    int getMin() {
        return aux.top();
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(x);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */