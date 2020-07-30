#include <string>
#include <vector>
#include <array>

#include "test_framework/generic_test.h"
using std::string;
using std::vector;
using std::array;

const array<string, 10> number_mapping = { "0", "1", "ABC", "DEF", "GHI", "JKL", "MNO", "PQRS", "TUV", "WXYZ" };

void Helper(const string& phone_number, int offset, string& partial_mnemonic, vector<string>& mnemonics){
  if(offset == phone_number.size()){
    mnemonics.emplace_back(partial_mnemonic);
    return;
  }

  for(char c : number_mapping[phone_number[offset] - '0']){
    partial_mnemonic[offset] = c;
    Helper(phone_number, offset + 1, partial_mnemonic, mnemonics);
  }

}

vector<string> PhoneMnemonic(const string& phone_number) {
  string partial_mnemonic(phone_number.size(), 0);
  vector<string> mnemonics;
  Helper(phone_number, 0, partial_mnemonic, mnemonics);
  return mnemonics;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"phone_number"};
  return GenericTestMain(args, "phone_number_mnemonic.cc",
                         "phone_number_mnemonic.tsv", &PhoneMnemonic,
                         UnorderedComparator{}, param_names);
}
