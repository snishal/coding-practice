#include <string>

#include "test_framework/generic_test.h"
using std::string;
bool IsPalindrome(const string& s) {
  int i = 0, j = s.size() - 1 ;

  while(i < j){
    while(!std::isalnum(s[i]) && i < j){
      i++;
    }
    while(!std::isalnum(s[j]) && i < j){
      j--;
    }

    if(std::tolower(s[i]) != std::tolower(s[j])){
      return false;
    }

    i++, j--;
  }

  return true;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"s"};
  return GenericTestMain(args, "is_string_palindromic_punctuation.cc",
                         "is_string_palindromic_punctuation.tsv", &IsPalindrome,
                         DefaultComparator{}, param_names);
}
