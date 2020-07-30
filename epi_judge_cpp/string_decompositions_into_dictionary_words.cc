#include <string>
#include <vector>
#include <unordered_map>

#include "test_framework/generic_test.h"
using std::string;
using std::vector;
using std::unordered_map;

bool MatchWordsInDict(const string& s, int start, const unordered_map<string, int>& freq, int num_words, int unit_size){
  unordered_map<string, int> curr_freq;
  for(int i = 0; i < num_words; i++){
    string curr_word = s.substr(start + i * unit_size, unit_size);
    auto iter = freq.find(curr_word);
    if(iter == freq.end()){
      return false;
    }
    if(++curr_freq[curr_word] > iter->second){
      return false;
    }
  }
  return true;
}

vector<int> FindAllSubstrings(const string& s, const vector<string>& words) {
  unordered_map<string, int> freq;
  for(const string& word : words){
    freq[word]++;
  }

  int unit_size = words.front().size();
  vector<int> result;
  for(int i = 0; i + unit_size * words.size() <= s.size(); i++){
    if(MatchWordsInDict(s, i, freq, words.size(), unit_size)){
      result.emplace_back(i);
    }
  }

  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"s", "words"};
  return GenericTestMain(args, "string_decompositions_into_dictionary_words.cc",
                         "string_decompositions_into_dictionary_words.tsv",
                         &FindAllSubstrings, DefaultComparator{}, param_names);
}
