class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        vector<vector<int>> d(grid.size(), vector<int>(grid[0].size(), numeric_limits<int>::max()));
        d[0][0] = grid[0][0];
        
        for(int i = 0; i < grid.size(); i++){
            for(int j = 0; j < grid[i].size(); j++){
                if(i > 0){
                    d[i][j] = min(d[i][j], d[i - 1][j] + grid[i][j]);
                }
                if(j > 0){
                    d[i][j] = min(d[i][j], d[i][j - 1] + grid[i][j]);
                }
            }
        }
        
        return d[d.size() - 1][d[0].size() - 1];
    }
};