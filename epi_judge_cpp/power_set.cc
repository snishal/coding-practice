#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

  vector<vector<int>> GeneratePowerSet(const vector<int>& input_set) {
    vector<vector<int>> power_set;
    for(int i = 0; i < (1 << input_set.size()); i++){
      int bit_array = i;
      vector<int> subset;
      while(bit_array){
        subset.emplace_back(input_set[std::log2(bit_array & ~(bit_array - 1))]);
        bit_array &= (bit_array - 1);
      }
      power_set.emplace_back(subset);
    }

    return power_set;
  }

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"input_set"};
  return GenericTestMain(args, "power_set.cc", "power_set.tsv",
                         &GeneratePowerSet, UnorderedComparator{}, param_names);
}
