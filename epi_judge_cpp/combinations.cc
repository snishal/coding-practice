#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

void Helper(int n, int k, int offset, vector<int>& partial_combination, vector<vector<int>>& combinations){
  if(partial_combination.size() == k){
    combinations.emplace_back(partial_combination);
    return;
  }

  int num_remaining = k - partial_combination.size();
  for(int i = offset; i <= n && i <= n - num_remaining + 1; i++){
    partial_combination.emplace_back(i);
    Helper(n, k, i + 1, partial_combination, combinations);
    partial_combination.pop_back();
  }
}

vector<vector<int>> Combinations(int n, int k) {
  vector<int> partial_combination;
  vector<vector<int>> combinations;

  Helper(n, k, 1, partial_combination, combinations);

  return combinations;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n", "k"};
  return GenericTestMain(args, "combinations.cc", "combinations.tsv",
                         &Combinations, UnorderedComparator{}, param_names);
}
