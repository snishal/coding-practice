#include <algorithm>
#include <string>
#include <vector>

#include "test_framework/generic_test.h"
using std::string;
using std::vector;

bool is_valid_portion(const string& s){
  if(s.size() > 3){
    return false;
  }

  if(s.front() == '0' && s.size() > 1){
    return false;
  }

  int val = std::stoi(s);
  return 0 <= val && val <= 255;
}

vector<string> GetValidIpAddress(const string& s) {
  vector<string> valid_ip_addresses;
  for(int i = 1 ; i < 4 && i < s.size(); i++){
    auto first = s.substr(0, i);
    if(is_valid_portion(first)){
      for(int j = 1; j < 4 && i + j < s.size(); j++){
        auto second = s.substr(i, j);
        if(is_valid_portion(second)){
          for(int k = 1; k < 4 && i + j + k < s.size(); k++){
            auto third = s.substr(i + j, k), forth = s.substr(i + j + k);
            if(is_valid_portion(third) && is_valid_portion(forth)){
              valid_ip_addresses.emplace_back(first + "." + second + "." + third + "." + forth);
            }
          }
        }
      }
    }
  }

  return valid_ip_addresses;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"s"};
  return GenericTestMain(args, "valid_ip_addresses.cc",
                         "valid_ip_addresses.tsv", &GetValidIpAddress,
                         UnorderedComparator{}, param_names);
}
