#include <stdexcept>
#include <vector>
#include <bitset>

#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
using std::invalid_argument;
using std::vector;
using std::bitset;

int FindMissingElement(vector<int>::const_iterator stream_begin,
                       const vector<int>::const_iterator& stream_end) {
  const int numBucket = 1 << 16;
  vector<int> count(numBucket, 0);
  vector<int>::const_iterator stream_begin_copy = stream_begin;

  while(stream_begin != stream_end){
    int upper_part = *stream_begin >> 16;
    ++count[upper_part], ++stream_begin;
  }

  const int bucketCapacity = 1 << 16;
  int candidateBucket;
  for(int i = 0; i < numBucket; ++i){
    if(count[i] < bucketCapacity){
      candidateBucket = i;
      break;
    }
  }

  bitset<bucketCapacity> candidates;
  stream_begin = stream_begin_copy;
  while(stream_begin != stream_end){
    int x = *stream_begin++;
    int upper_part = x >> 16;
    if(upper_part == candidateBucket){
      int lower_part = ((1 << 16) - 1) & x;
      candidates.set(lower_part);
    }
  }

  for(int i = 0; i < bucketCapacity; i++){
    if(candidates[i] == 0){
      return (candidateBucket << 16) | i;
    }
  }

  throw invalid_argument("no missing element");
}
void FindMissingElementWrapper(const vector<int>& stream) {
  try {
    int res = FindMissingElement(cbegin(stream), cend(stream));
    if (std::find(stream.begin(), stream.end(), res) != stream.end()) {
      throw TestFailure(std::to_string(res) + " appears in stream");
    }
  } catch (invalid_argument&) {
    throw TestFailure("Unexpected no missing element exception");
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"stream"};
  return GenericTestMain(args, "absent_value_array.cc",
                         "absent_value_array.tsv", &FindMissingElementWrapper,
                         DefaultComparator{}, param_names);
}
