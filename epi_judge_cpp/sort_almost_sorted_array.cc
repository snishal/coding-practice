#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
vector<int> SortApproximatelySortedData(
    vector<int>::const_iterator sequence_begin,
    const vector<int>::const_iterator& sequence_end, int k) {
	std::priority_queue<int, std::vector<int>, std::greater<int>> min_heap;
	vector<int> sorted_data;
	for(auto itr = sequence_begin; itr != sequence_end; itr = std::next(itr)){
		if(min_heap.size() == k){
			sorted_data.emplace_back(min_heap.top());
			min_heap.pop();
		}
		min_heap.push(*(itr));
	}

	while (!min_heap.empty()){
		sorted_data.emplace_back(min_heap.top());
		min_heap.pop();
	}

	return sorted_data;
	
}
vector<int> SortApproximatelySortedDataWrapper(const vector<int>& sequence,
                                               int k) {
  return SortApproximatelySortedData(cbegin(sequence), cend(sequence), k);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"sequence", "k"};
  return GenericTestMain(
      args, "sort_almost_sorted_array.cc", "sort_almost_sorted_array.tsv",
      &SortApproximatelySortedDataWrapper, DefaultComparator{}, param_names);
}
