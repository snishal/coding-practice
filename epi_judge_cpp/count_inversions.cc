#include <vector>
#include <random>

#include "test_framework/generic_test.h"
using std::vector;

int MergeSortAndCountInversions(vector<int>& A, int l, int m, int r){
  vector<int> sorted;
  int i = l, j = m, inversions = 0;
  while(i < m && j < r){
    if(A[i] <= A[j]){
      sorted.emplace_back(A[i++]);
    }else{
      inversions += m - i;
      sorted.emplace_back(A[j++]);
    }
  }
  std::copy(A.begin() + i, A.begin() + m, std::back_inserter(sorted));
  std::copy(A.begin() + j, A.begin() + r, std::back_inserter(sorted));

  std::copy(sorted.begin(), sorted.end(), A.begin() + l);
  return inversions;
}

int CountSubarrayInversions(vector<int>& A, int l, int r){
  if(r - l <= 1){
    return 0;
  }

  int m = l + ((r - l ) / 2);
  return CountSubarrayInversions(A, l, m) + CountSubarrayInversions(A, m, r) + MergeSortAndCountInversions(A, l, m, r);
}

int CountInversions(vector<int> A) {
  return CountSubarrayInversions(A, 0, A.size());
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "count_inversions.cc", "count_inversions.tsv",
                         &CountInversions, DefaultComparator{}, param_names);
}
