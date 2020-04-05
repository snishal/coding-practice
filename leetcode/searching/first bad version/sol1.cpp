// Forward declaration of isBadVersion API.
bool isBadVersion(int version);

class Solution {
public:
    int firstBadVersion(int n) {
        int l = 1, r = n, m, idx = -1;
        
        while(l <= r){
            m = l + (r - l)/2;
            
            auto flag = isBadVersion(m);
            if(flag){
                idx = m;
                r = m-1;
            }else{
                l = m+1;
            }
        }
        
        return idx;
    }
};