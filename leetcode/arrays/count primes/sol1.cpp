class Solution {
public:
    int countPrimes(int n) {
        int count = 0;
        vector<bool> is_prime(n+1, true);
        is_prime[0] = is_prime[1] = false;
        for(int p = 2; p < n; p++){
            if(is_prime[p]){
                count++;
                for(int i = p; i <= n; i+=p){
                    is_prime[i] = false;
                }
            }
        }
        
        return count;
    }
};