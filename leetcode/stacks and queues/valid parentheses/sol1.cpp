class Solution {
public:
    
    bool isValid(string s) {
        
        stack<char> brace;
        
        for(int i = 0; i < s.length(); i++){
            if(s[i] == '(' || s[i] == '{' || s[i] == '['){
                brace.push(s[i]);
            }else{
                if(brace.empty())return false;
                if(s[i] == '}' && brace.top() != '{')return false;
                if(s[i] == ')' && brace.top() != '(')return false;
                if(s[i] == ']' && brace.top() != '[')return false;
                brace.pop();
            }
        }
        
        return brace.empty();
        
    }
};