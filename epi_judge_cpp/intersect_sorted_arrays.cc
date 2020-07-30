#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

vector<int> IntersectTwoSortedArrays(const vector<int>& A,
                                     const vector<int>& B) {
  vector<int> intersection;
  int i = 0, j = 0;
  while(i < A.size() && j < B.size()){
    if(A[i] == B[j] && (i == 0 || A[i] != A[i - 1])){
      intersection.emplace_back(A[i]);
      i++, j++;
    }else if(A[i] < B[j]){
      i++;
    }else{
      j++;
    }
  }

  return intersection;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "B"};
  return GenericTestMain(
      args, "intersect_sorted_arrays.cc", "intersect_sorted_arrays.tsv",
      &IntersectTwoSortedArrays, DefaultComparator{}, param_names);
}
