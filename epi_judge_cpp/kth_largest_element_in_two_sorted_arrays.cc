#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

int FindKthInTwoSortedArrays(const vector<int>& A, const vector<int>& B,
                             int k) {
  // TODO - you fill in here.
  int l = std::max(0, static_cast<int>(k - B.size()));
  int r = std::min(k, static_cast<int>(A.size()));

  while(l < r){
    int m = l + (r - l) / 2;
    int A_m_1 = (m - 1 < 0 ? std::numeric_limits<int>::min() : A[m - 1]);
    int A_m = (m >= A.size() ? std::numeric_limits<int>::max() : A[m]);
    int B_k_m_1 = (k - m - 1 < 0 ? std::numeric_limits<int>::min() : B[k - m - 1]);
    int B_k_m = (k - m >= B.size() ? std::numeric_limits<int>::max() : B[k - m]);

    if(A_m < B_k_m_1){
      l = m + 1;
    }else if(A_m_1 > B_k_m){
      r = m - 1;
    }else{
      return std::max(A_m_1, B_k_m_1);
    }
  }
  int A_m_1 = (l - 1 < 0 ? std::numeric_limits<int>::min() : A[l - 1]);
  int B_k_m_1 = (k - l - 1 < 0 ? std::numeric_limits<int>::min() : B[k - l - 1]);
  return std::max(A_m_1, B_k_m_1);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "B", "k"};
  return GenericTestMain(args, "kth_largest_element_in_two_sorted_arrays.cc",
                         "kth_largest_element_in_two_sorted_arrays.tsv",
                         &FindKthInTwoSortedArrays, DefaultComparator{},
                         param_names);
}
