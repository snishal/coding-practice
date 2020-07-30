#include <vector>
#include <map>

#include "test_framework/generic_test.h"
using std::vector;
using std::multimap;

int FindClosestElementsInSortedArrays(
    const vector<vector<int>>& sorted_arrays) {
  struct IterTail{
    vector<int>::const_iterator iter, tail;
  };
  
  multimap<int, IterTail> iter_tail;
  for(const vector<int>& sorted_array : sorted_arrays){
    iter_tail.emplace(sorted_array.front(), IterTail{sorted_array.cbegin(), sorted_array.cend()});
  }

  int min_interval = std::numeric_limits<int>::max();
  while(true){
    int min_value = iter_tail.cbegin()->first;
    int max_value = iter_tail.crbegin()->first;

    min_interval = std::min(min_interval, max_value - min_value); 
    const auto next_min = std::next(iter_tail.cbegin()->second.iter);
    const auto next_tail = iter_tail.cbegin()->second.tail;

    if(next_min == next_tail){
      return min_interval;
    }

    iter_tail.emplace(*next_min, IterTail{next_min, next_tail});
    iter_tail.erase(iter_tail.cbegin());
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"sorted_arrays"};
  return GenericTestMain(args, "minimum_distance_3_sorted_arrays.cc",
                         "minimum_distance_3_sorted_arrays.tsv",
                         &FindClosestElementsInSortedArrays,
                         DefaultComparator{}, param_names);
}
