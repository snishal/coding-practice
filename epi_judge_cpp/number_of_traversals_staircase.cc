#include <vector>
#include "test_framework/generic_test.h"
using std::vector;

int NumberOfWaysToTop(int top, int maximum_step) {
  vector<int> ways(top + 1, 0);
  
  ways[0] = 1;
  for(int i = 1; i <= top; ++i){
    for(int j = i - 1; j >= 0 && i - j <= maximum_step; j--){
      ways[i] += ways[j];
    }
  }
  return ways.back();
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"top", "maximum_step"};
  return GenericTestMain(args, "number_of_traversals_staircase.cc",
                         "number_of_traversals_staircase.tsv",
                         &NumberOfWaysToTop, DefaultComparator{}, param_names);
}
