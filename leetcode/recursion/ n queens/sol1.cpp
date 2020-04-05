class Solution {
private:
    void Solver(const int& n, int row, vector<string>& board, vector<vector<string>>& placements){
        if(row == n){
            placements.emplace_back(board);
            return;
        }
        
        for(int col = 0; col < n; col++){
            if(isValid(board, n, row, col)){
                board[row][col] = 'Q';
                Solver(n, row + 1, board, placements);
                board[row][col] = '.';
            }
        }
        return;
    }
    
    bool isValid(vector<string>& board, const int& n, const int& row, const int& col){
        for(int i = 0; i < row; i++){
            if(board[i][col] == 'Q'){
                return false;
            }
        }
        for(int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--){
            if(board[i][j] == 'Q'){
                return false;
            }
        }
        for(int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++){
            if(board[i][j] == 'Q'){
                return false;
            }
        }
        
        return true;
    }
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> placements;
        
        vector<string> board(n, string(n, '.'));
        
        Solver(n, 0, board, placements);
        return placements;
    }
};