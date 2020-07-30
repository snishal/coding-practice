#include <vector>
#include <unordered_set>

#include "test_framework/generic_test.h"
using std::vector;
using std::unordered_set;

bool TestCollatzConjecture(int n) {
  unordered_set<long> verified_numbers;
  for(int i = 3; i <= n; i+=2){
    unordered_set<long> sequence;
    long test_i = i;
    while(test_i >= i){
      if(sequence.emplace(test_i).second == false){
        return false;
      }
      if(test_i % 2){
        if(verified_numbers.emplace(test_i).second == false){
          break;
        }
        long next_i = 3 * test_i + 1;
        if(next_i <= test_i){
          throw std::overflow_error("Overflow");
        }
        test_i = next_i;
      }else{
        test_i /= 2;
      }
    }
  }
  return true;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n"};
  return GenericTestMain(args, "collatz_checker.cc", "collatz_checker.tsv",
                         &TestCollatzConjecture, DefaultComparator{},
                         param_names);
}
