#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
using std::vector;

struct DuplicateAndMissing {
  int duplicate, missing;
};

DuplicateAndMissing FindDuplicateMissing(const vector<int>& A) {
  // TODO - you fill in here.
  int missing_xor_dup = 0;
  for(int i = 0; i < A.size(); i++){
    missing_xor_dup ^= i ^ A[i];
  }

  int differ_bit = missing_xor_dup & ~(missing_xor_dup - 1);
  int miss_or_dup = 0;
  for(int i = 0; i < A.size(); i++){
    if(i & differ_bit){
      miss_or_dup ^= i;
    }
    if(A[i] & differ_bit){
      miss_or_dup ^= A[i];
    }
  }

  for(int i = 0; i < A.size(); i++){
    if(A[i] == miss_or_dup){
      return {miss_or_dup, miss_or_dup ^ missing_xor_dup};
    }
  }
  return {miss_or_dup ^ missing_xor_dup, miss_or_dup};
}

namespace test_framework {
template <>
struct SerializationTrait<DuplicateAndMissing>
    : UserSerTrait<DuplicateAndMissing, int, int> {};
}  // namespace test_framework

bool operator==(const DuplicateAndMissing& lhs,
                const DuplicateAndMissing& rhs) {
  return std::tie(lhs.duplicate, lhs.missing) ==
         std::tie(rhs.duplicate, rhs.missing);
}

std::ostream& operator<<(std::ostream& out, const DuplicateAndMissing& x) {
  return out << "duplicate: " << x.duplicate << ", missing: " << x.missing;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(
      args, "search_for_missing_element.cc", "find_missing_and_duplicate.tsv",
      &FindDuplicateMissing, DefaultComparator{}, param_names);
}
