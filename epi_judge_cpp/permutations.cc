#include <bits/stdc++.h>

#include "test_framework/generic_test.h"
using namespace std;

void Generate(int i, vector<int>& permutation, vector<vector<int>>& permutations){
    if(i == permutation.size() - 1){
        permutations.emplace_back(permutation);
        return;
    }
    
    for(int j = i; j < permutation.size(); j++){
        swap(permutation[i], permutation[j]);
        Generate(i + 1, permutation, permutations);
        swap(permutation[i], permutation[j]);
    }
}

vector<vector<int>> Permutations(vector<int> A) {
  vector<vector<int>>permutations;
  Generate(0, A, permutations);
  
  return permutations;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "permutations.cc", "permutations.tsv",
                         &Permutations, UnorderedComparator{}, param_names);
}
