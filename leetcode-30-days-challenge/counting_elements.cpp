class Solution {
public:
    int countElements(vector<int>& arr) {
        if(arr.size() <= 1){
            return 0;
        }
        sort(arr.begin(), arr.end());
        int count = 0, times = 1;
        
        for(int i = 1; i < arr.size(); i++){
            if(arr[i] == arr[i - 1]){
                times++;
            }else if(arr[i] == arr[i - 1] + 1){
                count += times;
                times = 1;
            }else{
                times = 1;
            }
        }
        
        return count;
    }
};