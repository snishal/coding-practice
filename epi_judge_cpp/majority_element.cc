#include <string>
#include <vector>

#include "test_framework/generic_test.h"
using std::string;
using std::vector;

string MajoritySearch(vector<string>::const_iterator stream_begin,
                      const vector<string>::const_iterator stream_end) {
  auto itr = stream_begin;
  string majority_element;
  int i = 0;
  while(itr != stream_end){
    if(i == 0){
      majority_element = *itr;
      i = 1;
    }else if(majority_element == *itr){
      i++;
    }else{
      i--;
    }
    itr = next(itr);
  }
  return majority_element;
}
string MajoritySearchWrapper(const vector<string>& stream) {
  return MajoritySearch(cbegin(stream), cend(stream));
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"stream"};
  return GenericTestMain(args, "majority_element.cc", "majority_element.tsv",
                         &MajoritySearchWrapper, DefaultComparator{},
                         param_names);
}
