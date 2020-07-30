#include <string>

#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
using std::string;

string IntToString(int x) {

  if(x == std::numeric_limits<int>::min()){
    return "-2147483648";
  }
  string s = "";
  bool is_negative = false;
  if(x < 0){
    x = -x, is_negative = true;
  }

  do{
    s += '0' + (x % 10);
    x /= 10;
  }while(x);

  if(is_negative){
    s += "-";
  }

  std::reverse(s.begin(), s.end());

  return s;
}
int StringToInt(const string& s) {
  int val = 0;
  bool is_negative = s[0] == '-';

  for(int i = (s[0] == '+' || s[0] == '-' ) ? 1 : 0; i < s.size(); i++){
    val = val * 10 + (s[i] - '0');
  }

  return is_negative ? val * -1 : val;
}
void Wrapper(int x, const string& s) {
  if (stoi(IntToString(x)) != x) {
    throw TestFailure("Int to string conversion failed");
  }

  if (StringToInt(s) != x) {
    throw TestFailure("String to int conversion failed");
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x", "s"};
  return GenericTestMain(args, "string_integer_interconversion.cc",
                         "string_integer_interconversion.tsv", &Wrapper,
                         DefaultComparator{}, param_names);
}
