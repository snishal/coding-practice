#include <bits/stdc++.h>

#include "test_framework/generic_test.h"
using std::vector;

// The numbering starts from one, i.e., if A = [3, 1, -1, 2] then
// FindKthLargest(1, A) returns 3, FindKthLargest(2, A) returns 2,
// FindKthLargest(3, A) returns 1, and FindKthLargest(4, A) returns -1.

// Solution 1

5 6 7 2 3 1 4 10
2 1 3 4 7 5 6 10

template <typename Compare>
int Partition(vector<int>* A_ptr, int l, int r, int pivot, Compare comp){
  vector<int>& A = *A_ptr;

  int pivot_value = A[pivot];
  int new_pivot = l;
  std::swap(A[pivot], A[r]);

  for(int i = l; i < r; i++){
    if(comp(A[i], pivot_value)){
      std::swap(A[i], A[new_pivot++]);
    }
  }

  std::swap(A[r], A[new_pivot]);
  return new_pivot;
}

int FindKthLargest(int k, vector<int>* A_ptr) {
  vector<int>& A = *A_ptr;
  int l = 0, r = A.size() - 1;
  std::default_random_engine gen((std::random_device())());
  while(l <= r){
    int pivot = std::uniform_int_distribution<int>{l, r}(gen);
    int new_pivot = Partition(A_ptr, l, r, pivot, std::greater<int>());

    if(new_pivot == k - 1){
      return A[new_pivot];
    }else if(new_pivot > k - 1){
      r = new_pivot - 1;
    }else{
      l = new_pivot + 1;
    }
  }
}

// Solution 2
// int FindKthLargest(int k, vector<int>* A_ptr) {
//   vector<int>& A = *A_ptr;
//   std::partial_sort(A.begin(), A.begin() + k, A.end(), std::greater<int>());
//   return A[k - 1];
// }
int FindKthLargestWrapper(int k, vector<int>& A) {
  return FindKthLargest(k, &A);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"k", "A"};
  return GenericTestMain(args, "kth_largest_in_array.cc",
                         "kth_largest_in_array.tsv", &FindKthLargestWrapper,
                         DefaultComparator{}, param_names);
}
