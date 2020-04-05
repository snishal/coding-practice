// Solution 1
class Solution {
private:
    int nextSqNum(int n){
        int temp = 0;
        while(n){
            temp += pow(n % 10, 2);
            n /= 10;
        }
        
        return temp;
    }
public:
    bool isHappy(int n) {
        int slow , fast;
        slow = fast = n;
        
        do{
            slow = nextSqNum(slow);
            fast = nextSqNum(nextSqNum(fast));
        }while(slow != fast);
            
        return (slow == 1);
    }
};

//Solution 2
class Solution {
public:
    bool isHappy(int n) {
        unordered_set<int> s;
        int temp;
        
        while(n != 1){
            
            if(s.find(n) != s.end())return false;
            s.insert(n);
            
            temp = 0;
            while(n){
                temp += pow(n % 10, 2);
                n /= 10;
            }
            n = temp;
            
        }
        
        return true;
    }
};