#include <string>
#include <unordered_map>

#include "test_framework/generic_test.h"
using std::string;
using std::unordered_map;

bool IsLetterConstructibleFromMagazine(const string& letter_text,
                                       const string& magazine_text) {
  unordered_map<char, int> count;

  for(const char& ch : letter_text){
    count[ch]++;
  }

  for(const char& ch : magazine_text){
    auto it = count.find(ch);
    if(it != count.end()){
      --it->second;
      if(it->second == 0){
        count.erase(it);
        if(count.empty()){
          break;
        }
      }
    }
  }

  return count.empty();
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"letter_text", "magazine_text"};
  return GenericTestMain(args, "is_anonymous_letter_constructible.cc",
                         "is_anonymous_letter_constructible.tsv",
                         &IsLetterConstructibleFromMagazine,
                         DefaultComparator{}, param_names);
}
