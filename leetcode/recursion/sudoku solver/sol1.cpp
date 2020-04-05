class Solution {
public:
    void solveSudoku(vector<vector<char>>& board) {
        solveSudokuPartial(board, 0, 0);
    }
    
    bool solveSudokuPartial(vector<vector<char>>& board, int r, int c){
        if(r == board.size()){
            r = 0;
            if(++c == board[r].size()){
                return true;
            }
        }
        
        if(board[r][c] != '.'){
            return solveSudokuPartial(board, r + 1, c);
        }
        
        for(int val = 1; val <= board.size(); val++){
            if(canAddVal(board, r, c, val + '0')){
                board[r][c] = val + '0';
                if(solveSudokuPartial(board, r + 1, c)){
                    return true;
                }
            }
        }
        
        board[r][c] = '.';
        return false;
    }
    
    bool canAddVal(vector<vector<char>>& board, int r, int c, int val){
        for(int k = 0; k < board.size(); k++){
            if(val == board[k][c]){
                return false;
            }
        }
        
        for(int k = 0; k < board.size(); k++){
            if(val == board[r][k]){
                return false;
            }
        }
        
        int region_size = sqrt(board.size());
        int I = r / region_size, J = c / region_size;
        for(int i = 0; i < region_size; i++){
            for(int j = 0; j < region_size; j++){
                if(val == board[region_size * I + i][region_size * J + j]){
                    return false;
                }
            }
        }
        
        return true;
    }
};