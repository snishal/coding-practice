#include <string>
#include <vector>
#include <unordered_map>

#include "test_framework/generic_test.h"
using std::string;
using std::vector;
using std::unordered_map;

vector<vector<string>> FindAnagrams(const vector<string>& dictionary) {
  unordered_map<string, vector<string>> map;

  for(const string& word : dictionary){
    string sorted_word = word;
    sort(sorted_word.begin(), sorted_word.end());
    map[sorted_word].emplace_back(word);
  }

  vector<vector<string>> anangrams;

  for(const auto& pair : map){
    if(pair.second.size() > 1){
      anangrams.emplace_back(pair.second);
    }
  }

  return anangrams;
}

vector<vector<string>> FindAnagrams(const vector<string>& dictionary) {
  unordered_map<string, vector<string>> map;

  for(const string& word : dictionary){
    map[getHash(word)].emplace_back(word);
  }

  vector<vector<string>> anangrams;

  for(const auto& pair : map){
    if(pair.second.size() > 1){
      anangrams.emplace_back(pair.second);
    }
  }

  return anangrams;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"dictionary"};
  return GenericTestMain(args, "anagrams.cc", "anagrams.tsv", &FindAnagrams,
                         UnorderedComparator{}, param_names);
}
