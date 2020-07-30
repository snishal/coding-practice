#include <string>
#include <unordered_set>
#include <queue>

#include "test_framework/generic_test.h"
using std::string;
using std::unordered_set;
using std::queue;

int TransformString(unordered_set<string> D, const string& s, const string& t) {
  int steps = 0;
  queue<string> level;
  level.push(s);
  while(!level.empty()){
    int levelSize = level.size();
    for(int i = 0; i < levelSize; ++i){
      string node = level.front();
      level.pop();

      string candidate = node;
      for(int j = 0; j < candidate.size(); ++j){
        for(int k = 0; k < 26; ++k){
          candidate[j] = k + 'a';
          if(candidate == t){
            return steps + 1;
          }
          if(D.count(candidate) != 0){
            level.push(candidate);
            D.erase(candidate);
          }
        }
        candidate[j] = node[j];
      }
    }
    ++steps;
  }

  return -1;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"D", "s", "t"};
  return GenericTestMain(args, "string_transformability.cc",
                         "string_transformability.tsv", &TransformString,
                         DefaultComparator{}, param_names);
}
