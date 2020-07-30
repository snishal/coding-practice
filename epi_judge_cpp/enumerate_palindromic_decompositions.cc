#include <algorithm>
#include <iterator>
#include <string>
#include <vector>

#include "test_framework/generic_test.h"
using std::string;
using std::vector;

bool IsPalindrome(const string& s){
  int i = 0, j = s.size() - 1;
  while(i < j){
    if(s[i] != s[j]){
      return false;
    }
    ++i, --j;
  }
  return true;
}

void Helper(const string& text, int offset, vector<string>& decomposition, vector<vector<string>>& decompositions){
  if(offset == text.size()){
    decompositions.emplace_back(decomposition);
    return;
  }

  for(int i = offset + 1; i <= text.size(); i++){
    string prefix = text.substr(offset, i - offset);
    if(IsPalindrome(prefix)){
      decomposition.emplace_back(prefix);
      Helper(text, i, decomposition, decompositions);
      decomposition.pop_back();
    }
  }
}

vector<vector<string>> PalindromeDecompositions(const string& text) {
  // TODO - you fill in here.
  vector<vector<string>> decompositions;
  vector<string> decomposition;
  Helper(text, 0, decomposition, decompositions);
  return decompositions;
}
bool Comp(vector<vector<string>> expected, vector<vector<string>> result) {
  std::sort(begin(expected), end(expected));
  std::sort(begin(result), end(result));
  return expected == result;
};

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"text"};
  return GenericTestMain(args, "enumerate_palindromic_decompositions.cc",
                         "enumerate_palindromic_decompositions.tsv",
                         &PalindromeDecompositions, &Comp, param_names);
}
