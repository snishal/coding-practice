class Solution {
public:
    int mySqrt(int x) {
        int left = 0, right = x;
        long mid = -1, midSq = -1;
        
        while(left <= right){
            mid = left + (right - left)/2;
            midSq = mid * mid;
            
            if(midSq <= x){
                left = mid + 1;
            }else{
                right = mid - 1;
            }
        }
        
        return left - 1;
    }
};