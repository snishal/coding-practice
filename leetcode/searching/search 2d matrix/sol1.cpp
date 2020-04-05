class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        bool found = false;
        if(matrix.size() > 0){
            int i = 0, j = matrix[0].size() - 1;

            while(i < matrix.size() && j >= 0){
                if(matrix[i][j] == target){
                    found = true;
                    break;
                }else if(matrix[i][j] < target){
                    i++;
                }else{
                    j--;
                }
            }
        }
        
        return found;
    }
};