#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

int FindBiggestNMinusOneProduct(const vector<int>& A) {
  int negative_nums = 0, least_negative_idx = -1, greatest_negative_idx = -1, least_non_negative_idx = -1;

  for(int i = 0; i < A.size(); i++){
    if(A[i] < 0){
      negative_nums++;
      if(least_negative_idx == -1 || A[least_negative_idx] < A[i]){
        least_negative_idx = i;
      }
      if(greatest_negative_idx == -1 || A[i] < A[greatest_negative_idx]){
        greatest_negative_idx = i;
      }
    }else if(least_non_negative_idx == -1 || A[i] < A[least_non_negative_idx]){
      least_non_negative_idx = i;
    }
  }

  int idx_to_skip = (negative_nums % 2) ? least_negative_idx : (least_non_negative_idx == -1) ? greatest_negative_idx : least_non_negative_idx;

  int max_prod = 1;
  for(int i = 0; i < A.size(); i++){
    if(i != idx_to_skip){
      max_prod *= A[i];
    }
  }

  return max_prod;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(
      args, "max_product_all_but_one.cc", "max_product_all_but_one.tsv",
      &FindBiggestNMinusOneProduct, DefaultComparator{}, param_names);
}
