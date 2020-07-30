#include <string>
#include <stack>

#include "test_framework/generic_test.h"
using std::string;
using std::stack;

bool IsWellFormed(const string& s) {
  stack<char> leftParenthesis;

  for(const char& c : s){
    if(c == '(' || c == '{' || c == '['){
      leftParenthesis.push(c);
    }else{
      if(leftParenthesis.empty())return false;
      
      if(c == ')' && leftParenthesis.top() != '(')return false;
      if(c == '}' && leftParenthesis.top() != '{')return false;
      if(c == ']' && leftParenthesis.top() != '[')return false;

      leftParenthesis.pop();
    }
  }
  return leftParenthesis.empty();
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"s"};
  return GenericTestMain(args, "is_valid_parenthesization.cc",
                         "is_valid_parenthesization.tsv", &IsWellFormed,
                         DefaultComparator{}, param_names);
}
