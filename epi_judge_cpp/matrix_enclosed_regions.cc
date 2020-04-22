#include <stdexcept>
#include <string>
#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/timed_executor.h"
using std::string;
using std::vector;

void DFS(vector<vector<char>>& board, int r, int c){
  if(r < 0 || r >= board.size() || c < 0 || c >= board[r].size() || board[r][c] == 'B' || board[r][c] == 'T'){
    return;
  }

  board[r][c] = 'T';

  DFS(board, r - 1, c);
  DFS(board, r + 1, c);
  DFS(board, r, c - 1);
  DFS(board, r, c + 1);

  return;
}

void FillSurroundedRegions(vector<vector<char>>* board_ptr) {
  vector<vector<char>>& board = *board_ptr;
  
  for(int i = 0; i < board.size(); i++){
    DFS(board, i, 0);
    DFS(board, i, board[i].size() - 1);
  }

  for(int i = 0; i < board[0].size(); i++){
    DFS(board, 0, i);
    DFS(board, board.size() - 1, i);
  }

  for(int i = 0; i < board.size(); i++){
    for(int j = 0; j < board[i].size(); j++){
      board[i][j] = (board[i][j] == 'T') ? 'W' : 'B';
    }
  }

  return;
}
vector<vector<string>> FillSurroundedRegionsWrapper(
    TimedExecutor& executor, vector<vector<string>> board) {
  vector<vector<char>> char_vector;
  char_vector.resize(board.size());
  for (int i = 0; i < board.size(); i++) {
    for (const string& s : board[i]) {
      if (s.size() != 1) {
        throw std::runtime_error("String size is not 1");
      }
      char_vector[i].push_back(s[0]);
    }
  }

  executor.Run([&] { FillSurroundedRegions(&char_vector); });

  board.clear();
  board.resize(char_vector.size(), {});
  for (int i = 0; i < board.size(); i++) {
    for (char c : char_vector[i]) {
      board[i].emplace_back(1, c);
    }
  }

  return board;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "board"};
  return GenericTestMain(
      args, "matrix_enclosed_regions.cc", "matrix_enclosed_regions.tsv",
      &FillSurroundedRegionsWrapper, DefaultComparator{}, param_names);
}
