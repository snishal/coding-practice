class MyCircularQueue {
private:
    vector<int> q;
    int front, rear, size;
public:
    /** Initialize your data structure here. Set the size of the queue to be k. */
    MyCircularQueue(int k) {
        q.resize(k);
        front = 0;
        rear = -1;
        size = k;
    }
    
    /** Insert an element into the circular queue. Return true if the operation is successful. */
    bool enQueue(int value) {
        if(isFull()){
            return false;
        }
        rear = (rear + 1) % size;
        q[rear] = value;
        return true;
    }
    
    /** Delete an element from the circular queue. Return true if the operation is successful. */
    bool deQueue() {
        if(isEmpty())return false;
        if(front == rear){
            front = 0;
            rear = -1;
        }else{
            front = (front + 1) % size;
        }
        return true;
    }
    
    /** Get the front item from the queue. */
    int Front() {
        return isEmpty() ? -1 : q[front];
    }
    
    /** Get the last item from the queue. */
    int Rear() {
        return isEmpty() ? -1 : q[rear];
    }
    
    /** Checks whether the circular queue is empty or not. */
    bool isEmpty() {
        return rear == -1;
    }
    
    /** Checks whether the circular queue is full or not. */
    bool isFull() {
        return !isEmpty() && (rear + 1) % size == front;
    }
};

/**
 * Your MyCircularQueue object will be instantiated and called as such:
 * MyCircularQueue* obj = new MyCircularQueue(k);
 * bool param_1 = obj->enQueue(value);
 * bool param_2 = obj->deQueue();
 * int param_3 = obj->Front();
 * int param_4 = obj->Rear();
 * bool param_5 = obj->isEmpty();
 * bool param_6 = obj->isFull();
 */