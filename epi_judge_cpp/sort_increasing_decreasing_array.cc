#include <vector>

#include "test_framework/generic_test.h"

#define main _main
#include "sorted_arrays_merge.cc"
#undef main

using std::vector;
vector<int> SortKIncreasingDecreasingArray(const vector<int>& A) {
  vector<vector<int>> sorted_sub_arrays;
  typedef enum { Increasing, Decreasing } Subarray;
  Subarray subarray = Subarray::Increasing;
  int start_idx = 0;
  for(int i = 1; i <= A.size(); i++){
    if(i == A.size() || (A[i - 1] < A[i] && subarray == Subarray::Decreasing) || (A[i - 1] >= A[i] && subarray == Subarray::Increasing)){
      if(subarray == Subarray::Increasing){
        sorted_sub_arrays.emplace_back(A.cbegin() + start_idx, A.cbegin() + i);
      }else{
        sorted_sub_arrays.emplace_back(A.crbegin() + A.size() - i, A.crbegin() + A.size() - start_idx);
      }
      start_idx = i;
      subarray = (subarray == Subarray::Increasing) ? Subarray::Decreasing : Subarray::Increasing;
    }
  }

  return MergeSortedArrays(sorted_sub_arrays);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "sort_increasing_decreasing_array.cc",
                         "sort_increasing_decreasing_array.tsv",
                         &SortKIncreasingDecreasingArray, DefaultComparator{},
                         param_names);
}
