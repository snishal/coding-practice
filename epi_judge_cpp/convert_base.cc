#include <string>

#include "test_framework/generic_test.h"
using std::string;

string convertToBase(int x, int b2){
  
  string s = "";

  do{
    int digit = x % b2;
    s += (digit < 10) ? '0' + digit : 'A' + digit - 10;
    x /= b2;
  }while(x);

  std::reverse(s.begin(), s.end());

  return s;
}

string ConvertBase(const string& num_as_string, int b1, int b2) {
  bool is_negative = num_as_string.front() == '-';
  int num_base_10 = 0; 

  for(int i = is_negative ? 1 : 0; i < num_as_string.size(); i++){
    num_base_10 *= b1;
    num_base_10 += (std::isdigit(num_as_string[i]) ? num_as_string[i] - '0' : num_as_string[i] - 'A' + 10);
  }

  return (is_negative ? "-" : "") + convertToBase(num_base_10, b2);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"num_as_string", "b1", "b2"};
  return GenericTestMain(args, "convert_base.cc", "convert_base.tsv",
                         &ConvertBase, DefaultComparator{}, param_names);
}
