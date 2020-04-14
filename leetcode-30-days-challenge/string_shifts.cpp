class Solution {
private:
    void leftShift(int& pos, const int& size, int k){
        k = k % size;
        pos = pos - k;
        if(pos < 0){
            pos = size + pos;
        }
    }
    
    void rightShift(int& pos, const int& size, int k){
        k = k % size;
        pos += k;
        pos = pos % size;
    }
public:
    string stringShift(string s, vector<vector<int>>& shift) {
        int zeroPos = 0, len = s.size();
        
        for(const auto& pair : shift){
            if(pair[0] == 0){
                leftShift(zeroPos, len, pair[1]);
            }else if(pair[0] == 1){
                rightShift(zeroPos, len, pair[1]);
            }
        }
        
        std::rotate(s.rbegin(), s.rbegin() + zeroPos, s.rend());
        
        return s;
    }
};