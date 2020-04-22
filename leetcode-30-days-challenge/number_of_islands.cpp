class Solution {
private:
    void capture(vector<vector<char>>& grid, int r, int c){
        if(r < 0 || r >= grid.size() || c < 0 || c >= grid[r].size() || grid[r][c] == '0'){
            return;
        }
        
        grid[r][c] = '0';
        
        capture(grid, r - 1, c);
        capture(grid, r + 1, c);
        capture(grid, r, c - 1);
        capture(grid, r, c + 1);
        
        return;
    }
public:
    int numIslands(vector<vector<char>>& grid) {
        int islandCount = 0;
        for(int i = 0; i < grid.size(); i++){
            for(int j = 0; j < grid[i].size(); j++){
                if(grid[i][j] == '1'){
                    capture(grid, i, j);
                    islandCount++;
                }
            }
        }
        
        return islandCount;
    }
};