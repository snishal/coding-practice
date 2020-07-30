#include <algorithm>
#include <functional>
#include <unordered_map>
#include <vector>
#include <random>

#include "test_framework/generic_test.h"
#include "test_framework/random_sequence_checker.h"
#include "test_framework/timed_executor.h"
using std::abs;
using std::bind;
using std::unordered_map;
using std::vector;
int NonuniformRandomNumberGeneration(const vector<int>& values,
                                     const vector<double>& probabilities) {
  vector<double> partial_probabilities;
  partial_probabilities.emplace_back(0);
  std::partial_sum(probabilities.begin(), probabilities.end(), std::back_inserter(partial_probabilities));

  std::default_random_engine seed((std::random_device())());
  double uniform_0_1 = std::generate_canonical<double, std::numeric_limits<double>::digits>(seed);
  int i = std::distance(partial_probabilities.cbegin(), std::upper_bound(partial_probabilities.cbegin(), partial_probabilities.cend(), uniform_0_1)) - 1;

  return values[i];
}
bool NonuniformRandomNumberGenerationRunner(
    TimedExecutor& executor, const vector<int>& values,
    const vector<double>& probabilities) {
  constexpr int kN = 1000000;
  vector<int> results;

  executor.Run([&] {
    for (int i = 0; i < kN; ++i) {
      results.emplace_back(
          NonuniformRandomNumberGeneration(values, probabilities));
    }
  });

  unordered_map<int, int> counts;
  for (int result : results) {
    ++counts[result];
  }
  for (int i = 0; i < values.size(); ++i) {
    const int v = values[i];
    const double p = probabilities[i];
    if (kN * p < 50 || kN * (1.0 - p) < 50) {
      continue;
    }
    const double sigma = sqrt(kN * p * (1.0 - p));
    if (abs(counts[v] - (p * kN)) > 5 * sigma) {
      return false;
    }
  }
  return true;
}

void NonuniformRandomNumberGenerationWrapper(
    TimedExecutor& executor, const vector<int>& values,
    const vector<double>& probabilities) {
  RunFuncWithRetries(bind(NonuniformRandomNumberGenerationRunner,
                          std::ref(executor), std::cref(values),
                          std::cref(probabilities)));
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "values", "probabilities"};
  return GenericTestMain(args, "nonuniform_random_number.cc",
                         "nonuniform_random_number.tsv",
                         &NonuniformRandomNumberGenerationWrapper,
                         DefaultComparator{}, param_names);
}
