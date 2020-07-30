#include <string>
#include <vector>

#include "test_framework/generic_test.h"
using std::string;
using std::vector;

void Generate(int left_parens, int right_parens, string s, vector<string>& valid_parens){
  if(left_parens == 0 && right_parens == 0){
    valid_parens.emplace_back(s);
  }
  if(left_parens > 0){
    Generate(left_parens - 1, right_parens, s + '(', valid_parens);
  }
  if(right_parens > left_parens){
    Generate(left_parens, right_parens - 1, s + ')', valid_parens);
  }
}

vector<string> GenerateBalancedParentheses(int num_pairs) {
  vector<string> valid_parens;
  Generate(num_pairs, num_pairs, "", valid_parens);
  return valid_parens;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"num_pairs"};
  return GenericTestMain(args, "enumerate_balanced_parentheses.cc",
                         "enumerate_balanced_parentheses.tsv",
                         &GenerateBalancedParentheses, UnorderedComparator{},
                         param_names);
}
