#include <string>
#include <unordered_set>

#include "test_framework/generic_test.h"
using std::string;
using std::unordered_set;

// Solution 1
// bool CanFormPalindrome(const string& s) {
//   unordered_map<char, int> count;

//   for(const char& ch : s){
//     count[ch]++;
//   }

//   int oddCount = 0;
//   for(const auto& pair : count){
//     if(pair.second % 2 != 0){
//       oddCount++;
//     }
//     if(oddCount == 2){
//       return false;
//     }
//   }

//   return true;
// }

// Solution 2
bool CanFormPalindrome(const string& s) {
  unordered_set<char> appeared;

  for(const char& ch : s){
    if(appeared.count(ch)){
      appeared.erase(ch);
    }else{
      appeared.insert(ch);
    }
  }

  return appeared.size() <= 1;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"s"};
  return GenericTestMain(args, "is_string_permutable_to_palindrome.cc",
                         "is_string_permutable_to_palindrome.tsv",
                         &CanFormPalindrome, DefaultComparator{}, param_names);
}
