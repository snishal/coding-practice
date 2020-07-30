#include <memory>
#include <vector>

#include "bst_node.h"
#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
using std::unique_ptr;
using std::vector;

struct Interval {
  int left, right;
};

void Helper(const unique_ptr<BstNode<int>>& tree, const Interval& interval, vector<int>& result){
  if(tree){
    if(tree->data < interval.left){
      Helper(tree->right, interval, result);
    }else if(tree->data > interval.right){
      Helper(tree->left, interval, result);
    }else{
      Helper(tree->left, interval, result);
      result.emplace_back(tree->data);
      Helper(tree->right, interval, result);
    }
  }
}

vector<int> RangeLookupInBST(const unique_ptr<BstNode<int>>& tree,
                             const Interval& interval) {
  // TODO - you fill in here.
  vector<int> result;
  Helper(tree, interval, result);
  return result;
}
void RangeLookupInBSTHelper(const unique_ptr<BstNode<int>>& tree,
                            const Interval& interval, vector<int>* result) {}

namespace test_framework {
template <>
struct SerializationTrait<Interval> : UserSerTrait<Interval, int, int> {
  static std::vector<std::string> GetMetricNames(const std::string& arg_name) {
    return {FmtStr("length({})", arg_name)};
  }

  static std::vector<int> GetMetrics(const Interval& x) {
    return {x.right - x.left};
  }
};
}  // namespace test_framework

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree", "interval"};
  return GenericTestMain(args, "range_lookup_in_bst.cc",
                         "range_lookup_in_bst.tsv", &RangeLookupInBST,
                         DefaultComparator{}, param_names);
}
