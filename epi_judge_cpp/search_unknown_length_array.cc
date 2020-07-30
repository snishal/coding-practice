#include <vector>
#include <exception>

#include "test_framework/generic_test.h"
using std::vector;
using std::exception;

int BinarySearchUnknownLength(const vector<int>& A, int k) {
  // TODO - you fill in here.
  int p = 0;
  while(true){
    try{
      int idx = (1 << p) - 1;
      if(A.at(idx) == k){
        return idx;
      }else if(A.at(idx) > k){
        break;
      }
    }catch(const exception&){
      break;
    }
    ++p;
  }
 
  int left = std::max(0, 1 << (p - 1)), right = (1 << p) - 2;
  while(left <= right){
    int mid = left + (right - left) * 0.5;
    try{
      if(A.at(mid) == k){
        return mid;
      }else if(A.at(mid) < k){
        left = mid + 1;
      }else{
        right = mid - 1;
      }
    }catch(const exception& e){
      right = mid - 1;
    }
  }
  return -1;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "k"};
  return GenericTestMain(
      args, "search_unknown_length_array.cc", "search_unknown_length_array.tsv",
      &BinarySearchUnknownLength, DefaultComparator{}, param_names);
}
