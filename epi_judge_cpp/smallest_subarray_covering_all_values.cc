#include <string>
#include <vector>
#include <unordered_map>

#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::string;
using std::vector;
using std::unordered_map;

struct Subarray {
  // Represent subarray by starting and ending indices, inclusive.
  int start, end;
};

Subarray FindSmallestSequentiallyCoveringSubset(
    const vector<string>& paragraph, const vector<string>& keywords) {
  unordered_map<string, int> keywords_to_idx;
  for(int i = 0; i < keywords.size(); i++){
    keywords_to_idx[keywords[i]] = i;
  }

  vector<int> latest_occurence(keywords.size(), -1);
  vector<int> shortest_subarray_length(keywords.size(), std::numeric_limits<int>::max());

  int shortest_dist = std::numeric_limits<int>::max();
  Subarray min_window = {-1, -1};
  for(int i = 0; i < paragraph.size(); i++){
    if(keywords_to_idx.count(paragraph[i])){
      int keyword_idx = keywords_to_idx.find(paragraph[i])->second;
      if(keyword_idx == 0){
        shortest_subarray_length[keyword_idx] = 1;
      }else if(shortest_subarray_length[keyword_idx - 1] != std::numeric_limits<int>::max()){
        shortest_subarray_length[keyword_idx] = shortest_subarray_length[keyword_idx - 1] + i - latest_occurence[keyword_idx - 1];
      }
      latest_occurence[keyword_idx] = i;

      if(keyword_idx == keywords.size() - 1 && shortest_subarray_length.back() < shortest_dist){
        shortest_dist = shortest_subarray_length.back();
        min_window = {i - shortest_subarray_length.back() + 1, i};
      }
    }
  }

  return min_window;
}
int FindSmallestSequentiallyCoveringSubsetWrapper(
    TimedExecutor& executor, const vector<string>& paragraph,
    const vector<string>& keywords) {
  auto result = executor.Run([&] {
    return FindSmallestSequentiallyCoveringSubset(paragraph, keywords);
  });

  int kw_idx = 0;
  if (result.start < 0) {
    throw TestFailure("Subarray start index is negative");
  }
  int para_idx = result.start;

  while (kw_idx < keywords.size()) {
    if (para_idx >= paragraph.size()) {
      throw TestFailure("Not all keywords are in the generated subarray");
    }
    if (para_idx >= paragraph.size()) {
      throw TestFailure("Subarray end index exceeds array size");
    }
    if (paragraph[para_idx] == keywords[kw_idx]) {
      kw_idx++;
    }
    para_idx++;
  }
  return result.end - result.start + 1;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "paragraph", "keywords"};
  return GenericTestMain(args, "smallest_subarray_covering_all_values.cc",
                         "smallest_subarray_covering_all_values.tsv",
                         &FindSmallestSequentiallyCoveringSubsetWrapper,
                         DefaultComparator{}, param_names);
}
