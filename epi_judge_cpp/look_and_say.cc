#include <string>

#include "test_framework/generic_test.h"
using std::string;

string next_num(string n){
  string next = "";
  int count = 1;
  for(int i = 1; i < n.size(); i++){
    if(n[i] == n[i - 1]){
      count++;
    }else{
      next += std::to_string(count) + n[i-1];
      count = 1;
    }
  }
  next += std::to_string(count) + n.back();

  return next;
}

string LookAndSay(int n) {
  string num = "1";
  for(int i = 1; i < n; i++){
    num = next_num(num);
  }
  return num;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n"};
  return GenericTestMain(args, "look_and_say.cc", "look_and_say.tsv",
                         &LookAndSay, DefaultComparator{}, param_names);
}
