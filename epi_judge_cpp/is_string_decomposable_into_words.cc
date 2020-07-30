#include <string>
#include <unordered_set>
#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::string;
using std::unordered_set;
using std::vector;

vector<string> DecomposeIntoDictionaryWords(const string& domain, const unordered_set<string>& dictionary) {
	vector<int> last_length(domain.size(), -1);

  for(int i = 0; i < domain.size(); i++){
    if(dictionary.find(domain.substr(0, i + 1)) != dictionary.end()){
      last_length[i] = i + 1;
    }

    if(last_length[i] == -1){
      for(int j = 0; j < i; j++){
        if(last_length[j] != -1 && dictionary.find(domain.substr(j + 1, i - j)) != dictionary.end()){
          last_length[i] = i - j;
          break;
        }   
      }
    }
  }

  vector<string> decompositions;
  if(last_length.back() != -1){
    int idx = domain.size() - 1;
    while(idx >= 0){
      decompositions.emplace_back(domain.substr(idx + 1 - last_length[idx], last_length[idx]));
      idx -= last_length[idx];
    }
    std::reverse(decompositions.begin(), decompositions.end());
  }
  return decompositions;
}
void DecomposeIntoDictionaryWordsWrapper(
    TimedExecutor& executor, const string& domain,
    const unordered_set<string>& dictionary, bool decomposable) {
  vector<string> result = executor.Run(
      [&] { return DecomposeIntoDictionaryWords(domain, dictionary); });
  if (!decomposable) {
    if (!result.empty()) {
      throw TestFailure("domain is not decomposable");
    }
    return;
  }

  if (std::any_of(std::begin(result), std::end(result),
                  [&](const std::string& s) { return !dictionary.count(s); })) {
    throw TestFailure("Result uses words not in dictionary");
  }

  if (std::accumulate(std::begin(result), std::end(result), string()) !=
      domain) {
    throw TestFailure("Result is not composed into domain");
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "domain", "dictionary",
                                       "decomposable"};
  return GenericTestMain(args, "is_string_decomposable_into_words.cc",
                         "is_string_decomposable_into_words.tsv",
                         &DecomposeIntoDictionaryWordsWrapper,
                         DefaultComparator{}, param_names);
}
