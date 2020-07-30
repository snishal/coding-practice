#include <vector>
#include <queue>

#include "test_framework/generic_test.h"
using std::vector;
using std::priority_queue;

struct CurrEndIterator{
  vector<int>::const_iterator curr, end;
  
  bool operator>(const CurrEndIterator& that) const {
    return (*curr) > (*that.curr);
  }
};

vector<int> MergeSortedArrays(const vector<vector<int>>& sorted_arrays) {
  priority_queue<CurrEndIterator, vector<CurrEndIterator>, std::greater<>> min_heap;

  for(const vector<int>& sorted_array : sorted_arrays){
    min_heap.emplace(CurrEndIterator{sorted_array.cbegin(), sorted_array.cend()});
  }

  vector<int> sorted_array;
  while(!min_heap.empty()){
    auto smallest = min_heap.top();
    min_heap.pop();
    
    if(smallest.curr != smallest.end){
      sorted_array.emplace_back(*smallest.curr);
      min_heap.emplace(CurrEndIterator{next(smallest.curr), smallest.end});
    }
  }

  return sorted_array;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"sorted_arrays"};
  return GenericTestMain(args, "sorted_arrays_merge.cc",
                         "sorted_arrays_merge.tsv", &MergeSortedArrays,
                         DefaultComparator{}, param_names);
}
