#include <vector>
#include <queue>

#include "test_framework/generic_test.h"
using std::vector;
using std::priority_queue;

// Solution 1
// vector<double> OnlineMedian(vector<int>::const_iterator sequence_begin,
//                             const vector<int>::const_iterator& sequence_end) {
//   // TODO - you fill in here.
//   priority_queue<int, vector<int>, std::greater<>> min_heap;
//   priority_queue<int, vector<int>, std::less<>> max_heap;

//   vector<double> median;

//   for(auto it = sequence_begin; it != sequence_end; it = next(it)){
//     if(min_heap.empty()){
//       min_heap.emplace(*it);
//     }else{
//       if(*it >= min_heap.top()){
//         min_heap.emplace(*it);
//       }else{
//         max_heap.emplace(*it);
//       }
//     }

//     if(min_heap.size() > max_heap.size() + 1){
//       max_heap.emplace(min_heap.top());
//       min_heap.pop();
//     }else if(max_heap.size() > min_heap.size()){
//       min_heap.emplace(max_heap.top());
//       max_heap.pop();
//     }
//     median.emplace_back(min_heap.size() == max_heap.size() ? (0.5 * (min_heap.top() + max_heap.top())) : min_heap.top());
//   }

//   return median;
// }

// Solution 2
vector<double> OnlineMedian(vector<int>::const_iterator sequence_begin,
                            const vector<int>::const_iterator& sequence_end) {
  // TODO - you fill in here.
  priority_queue<int, vector<int>, std::greater<>> min_heap;
  priority_queue<int, vector<int>, std::less<>> max_heap;

  vector<double> median;

  for(auto it = sequence_begin; it != sequence_end; it = next(it)){
    min_heap.emplace(*it);
    max_heap.emplace(min_heap.top());
    min_heap.pop();

    if(max_heap.size() > min_heap.size()){
      min_heap.emplace(max_heap.top());
      max_heap.pop();
    }

    median.emplace_back(min_heap.size() == max_heap.size() ? (0.5 * (min_heap.top() + max_heap.top())) : min_heap.top());
  }

  return median;
}

vector<double> OnlineMedianWrapper(const vector<int>& sequence) {
  return OnlineMedian(cbegin(sequence), cend(sequence));
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"sequence"};
  return GenericTestMain(args, "online_median.cc", "online_median.tsv",
                         &OnlineMedianWrapper, DefaultComparator{},
                         param_names);
}
