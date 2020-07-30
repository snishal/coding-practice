#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

int CalculateBonus(const vector<int>& productivity) {
  vector<int> tickets(productivity.size(), 1);

  for(int i = 1; i < productivity.size(); i++){
    if(productivity[i - 1] < productivity[i] && tickets[i] <= tickets[i - 1]){
      tickets[i] = tickets[i - 1] + 1;
    }
  }

  for(int i = productivity.size() - 2; i >= 0; i--){
    if(productivity[i + 1] < productivity[i] && tickets[i] <= tickets[i + 1]){
      tickets[i] = tickets[i + 1] + 1;
    }
  }
  
  return std::accumulate(tickets.begin(), tickets.end(), 0);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"productivity"};
  return GenericTestMain(args, "bonus.cc", "bonus.tsv", &CalculateBonus,
                         DefaultComparator{}, param_names);
}
