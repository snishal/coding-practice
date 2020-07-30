#include <vector>
#include <unordered_set>

#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
using std::vector;
using std::unordered_set;

struct Jug {
  int low, high;
};

struct VolumeRane{
  int low, high;

  bool operator==(const VolumeRane& that) const {
    return low == that.low && high == that.high;
  }
};

struct HashVolumeRange{
  size_t operator()(const VolumeRane& v) const {
    return std::hash<int>()(v.low) ^ std::hash<int>()(v.high);
  }
};

bool CheckFeasibleHelper(const vector<Jug>& jugs, int L, int H, unordered_set<VolumeRane, HashVolumeRange>* checked){
  if(L > H || checked->find({L, H}) != checked->end() || (L < 0 && H < 0)){
    return false;
  }

  for(const Jug& j : jugs){
    if((L <= j.low && j.high <= H) || CheckFeasibleHelper(jugs, L - j.low, H - j.high, checked)){
      return true;
    }
  }
  checked->emplace(VolumeRane{L, H});
  return false;
}

bool CheckFeasible(const vector<Jug>& jugs, int L, int H) {
  // TODO - you fill in here.
  return CheckFeasibleHelper(jugs, L, H, new unordered_set<VolumeRane, HashVolumeRange>);
}

namespace test_framework {
template <>
struct SerializationTrait<Jug> : UserSerTrait<Jug, int, int> {};
}  // namespace test_framework

bool operator==(const Jug& lhs, const Jug& rhs) {
  return lhs.low == rhs.low && lhs.high == rhs.high;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"jugs", "L", "H"};
  return GenericTestMain(args, "defective_jugs.cc", "defective_jugs.tsv",
                         &CheckFeasible, DefaultComparator{}, param_names);
}
