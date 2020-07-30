#include <string>
#include <vector>
#include <unordered_map>

#include "test_framework/generic_test.h"
using std::string;
using std::vector;
using std::unordered_map;

int FindNearestRepetition(const vector<string>& paragraph) {
  unordered_map<string, int> rightmost;

  int nearest = paragraph.size() + 1;
  for(int i = 0; i < paragraph.size(); i++){
    if(rightmost.count(paragraph[i]) > 0){
      nearest = std::min(nearest, i - rightmost[paragraph[i]]);
    }
    rightmost[paragraph[i]] = i;
  }
  
  return (nearest == paragraph.size()  +1 ? -1 : nearest);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"paragraph"};
  return GenericTestMain(args, "nearest_repeated_entries.cc",
                         "nearest_repeated_entries.tsv", &FindNearestRepetition,
                         DefaultComparator{}, param_names);
}
