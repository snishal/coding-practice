#include <vector>
#include <queue>

#include "test_framework/generic_test.h"
using std::vector;
using std::priority_queue;

vector<int> KLargestInBinaryHeap(const vector<int>& A, int k) {
  if(k <= 0){
    return {};
  }

  struct HeapEntry{
    int i, n;

    bool operator<(const HeapEntry& that) const {
      return n < that.n;
    }
  };

  priority_queue<HeapEntry, vector<HeapEntry>, std::less<>> max_heap;
  max_heap.push(HeapEntry{0, A[0]});

  vector<int> k_largest;
  for(int i = 0; i < k && !max_heap.empty(); i++){
    auto largest = max_heap.top();
    max_heap.pop();
    k_largest.emplace_back(largest.n);

    int left_child = 2 * largest.i + 1;
    if(left_child < A.size()){
      max_heap.emplace(HeapEntry{left_child, A[left_child]});
    }

    int right_child = 2 * largest.i + 2;
    if(right_child < A.size()){
      max_heap.emplace(HeapEntry{right_child, A[right_child]});
    }
  }

  return k_largest;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "k"};
  return GenericTestMain(args, "k_largest_in_heap.cc", "k_largest_in_heap.tsv",
                         &KLargestInBinaryHeap, UnorderedComparator{},
                         param_names);
}
