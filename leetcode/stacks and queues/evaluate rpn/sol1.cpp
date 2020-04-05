class Solution {
public:
    
    int evalRPN(vector<string>& tokens) {
        
        stack<int> s;
        int op1, op2;
        
        for(string token : tokens){
            if(token == "+" ){
                
                op1 = s.top();
                s.pop();
                
                op2 = s.top();
                s.pop();
                
                s.push(op2 + op1);
                
            }else if(token == "-" ){
                
                op1 = s.top();
                s.pop();
                
                op2 = s.top();
                s.pop();
                
                s.push(op2 - op1);
                
            }else if(token == "*" ){
                
                op1 = s.top();
                s.pop();
                
                op2 = s.top();
                s.pop();
                
                s.push(op2 * op1);
                
            }else if(token == "/" ){
                
                op1 = s.top();
                s.pop();
                
                op2 = s.top();
                s.pop();
                
                s.push(op2 / op1);
                
            }else{
                s.push(stoi(token));         
            }
        
        }
        
        return s.top();
        
    }
};