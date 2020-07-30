#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
int HIndex(vector<int> citations) {
  // TODO - you fill in here.
  std::sort(citations.begin(), citations.end());
  
  int l = 0, r = citations.size() - 1, h_idx = 0, m;

  while(l <= r){
    m = l + (r - l) * 0.5;
    if(citations[m] >= citations.size() - m){
      h_idx = citations.size() - m;
      r = m - 1;
    }else if(citations[m] < citations.size() - m){
      l = m + 1;
    }else{
      r = m - 1;
    }
  }
  return h_idx;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"citations"};
  return GenericTestMain(args, "h_index.cc", "h_index.tsv", &HIndex,
                         DefaultComparator{}, param_names);
}
