#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

void MergeTwoSortedArrays(vector<int>& A, int m, const vector<int>& B, int n) {
  int i  = m - 1, j = n - 1, write_idx = m + n - 1;
  while(i >= 0 && j >= 0){
    if(A[i] >= B[j]){
      A[write_idx--] = A[i--];
    }else{
      A[write_idx--] = B[j--];
    }
  }
  while(j >= 0){
    A[write_idx--] = B[j--];
  }
}
vector<int> MergeTwoSortedArraysWrapper(vector<int> A, int m,
                                        const vector<int>& B, int n) {
  MergeTwoSortedArrays(A, m, B, n);
  return A;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "m", "B", "n"};
  return GenericTestMain(
      args, "two_sorted_arrays_merge.cc", "two_sorted_arrays_merge.tsv",
      &MergeTwoSortedArraysWrapper, DefaultComparator{}, param_names);
}
