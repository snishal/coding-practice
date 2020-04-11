// Solution 1
class Solution {
private:
    string build(string S){
        string SNew;
        stack<char> s;
        
        for(const char& ch : S){
            if(ch == '#'){
                if(!s.empty()){
                    s.pop();
                }
            }else{
                s.push(ch);
            }
        }
        
        while(!s.empty()){
            SNew = s.top() + SNew;
            s.pop();
        }
        
        return SNew;
    }
public:
    bool backspaceCompare(string S, string T) {
     
        return build(S) == build(T);
        
    }
};

// Solution 2
class Solution {
public:
    bool backspaceCompare(string S, string T) {
        int valid_idx_s = S.size() - 1, valid_idx_t = T.size() - 1;
        int skip_s = 0, skip_t = 0;
        
        while(valid_idx_s >= 0 || valid_idx_t >= 0){
            skip_s = skip_t = 0;
            while(valid_idx_s >= 0){
                if(S[valid_idx_s] == '#'){
                    valid_idx_s--;
                    skip_s++;
                }else if(skip_s > 0){
                    skip_s--;
                    valid_idx_s--;
                }else{
                    break;
                }
            }
            while(valid_idx_t >= 0){
                if(T[valid_idx_t] == '#'){
                    valid_idx_t--;
                    skip_t++;
                }else if(skip_t > 0){
                    skip_t--;
                    valid_idx_t--;
                }else{
                    break;
                }
            }
            
            if(valid_idx_s >= 0 && valid_idx_t >= 0 && S[valid_idx_s] != T[valid_idx_t]){
                return false;
            }
            if ((valid_idx_s >= 0) != (valid_idx_t >= 0)){
                return false;
            }
            valid_idx_s--;
            valid_idx_t--;
        }
        
        return true;
    }
};