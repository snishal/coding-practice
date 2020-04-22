#include <string>
#include <unordered_set>
#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::string;
using std::unordered_set;
using std::vector;

bool DecomposeIntoDictionaryWordsHelper(const string& domain, int offset, const unordered_set<string>& dictionary, vector<string>& sequence) {
	if(offset == domain.size()){
		return true;
	}
	for(int i = offset + 1; i <= domain.size(); i++){
		string s1 = domain.substr(offset, i - offset);
		std::cout << s1 << std::endl;
		if(dictionary.count(s1) > 0){
			sequence.push_back(s1);
			if(DecomposeIntoDictionaryWordsHelper(domain, i, dictionary, sequence)){
				return true;
			}else{
				sequence.pop_back();
			}
		}
	}
	return false;
}

vector<string> DecomposeIntoDictionaryWords(const string& domain, const unordered_set<string>& dictionary) {
	vector<string> sequence;
	DecomposeIntoDictionaryWordsHelper(domain, 0, dictionary, sequence);
	return sequence;
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
