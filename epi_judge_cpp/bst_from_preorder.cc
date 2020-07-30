#include <memory>

#include "bst_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;
using std::vector;

unique_ptr<BstNode<int>> Helper(const vector<int>& preorder_sequence, int& i, int max_range){
  if(i >= preorder_sequence.size() || preorder_sequence[i] > max_range){
    return nullptr;
  }

  int node_val = preorder_sequence[i++];

  return std::make_unique<BstNode<int>>(BstNode<int>{
    node_val,
    Helper(preorder_sequence, i, node_val),
    Helper(preorder_sequence, i, max_range)
  });
}

unique_ptr<BstNode<int>> RebuildBSTFromPreorder(
    const vector<int>& preorder_sequence) {
  int start = 0;
  return Helper(preorder_sequence, start, std::numeric_limits<int>::max());
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"preorder_sequence"};
  return GenericTestMain(args, "bst_from_preorder.cc", "bst_from_preorder.tsv",
                         &RebuildBSTFromPreorder, DefaultComparator{},
                         param_names);
}
