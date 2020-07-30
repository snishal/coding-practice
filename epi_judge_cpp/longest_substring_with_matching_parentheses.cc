#include <string>
#include <vector>
#include <stack>

#include "test_framework/generic_test.h"
using std::string;
using std::vector;
using std::stack;

int LongestMatchingParentheses(const string& s) {
  int longest = 0, end = -1;
  stack<int> left_paren_idx;

  for(int i = 0; i < s.size(); i++){
    if(s[i] == '('){
      left_paren_idx.emplace(i);
    }else if(left_paren_idx.empty()){
      end = i;
    }else{
      left_paren_idx.pop();
      int start = left_paren_idx.empty() ? end : left_paren_idx.top();
      longest = std::max(longest, i - start);
    }
  }

  return longest;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"s"};
  return GenericTestMain(args, "longest_substring_with_matching_parentheses.cc",
                         "longest_substring_with_matching_parentheses.tsv",
                         &LongestMatchingParentheses, DefaultComparator{},
                         param_names);
}
