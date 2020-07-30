#include <string>

#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
using std::string;
string Decoding(const string &s) {
  // TODO - you fill in here.
  string result = "";
  int count = 0;

  for(const char& c : s){
    if(std::isdigit(c)){
      count = count * 10 + (c - '0');
    }else{
      result.append(count, c);
      count = 0;
    }
  }

  return result;
}
string Encoding(const string &s) {
  int count = 1;
  string result = "";

  for(int i = 1; i < s.size(); i++){
    if(s[i] == s[i - 1]){
      count++;
    }else{
      result += std::to_string(count) + s[i - 1];
      count = 1;
    }
  }
  result += std::to_string(count) + s.back();

  return result;
}
void RleTester(const string &encoded, const string &decoded) {
  if (Decoding(encoded) != decoded) {
    throw TestFailure("Decoding failed");
  }
  if (Encoding(decoded) != encoded) {
    throw TestFailure("Encoding failed");
  }
}

int main(int argc, char *argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"encoded", "decoded"};
  return GenericTestMain(args, "run_length_compression.cc",
                         "run_length_compression.tsv", &RleTester,
                         DefaultComparator{}, param_names);
}
