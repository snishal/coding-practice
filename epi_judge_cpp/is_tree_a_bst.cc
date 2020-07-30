#include <memory>

#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;

bool AreKeysInRange(const unique_ptr<BinaryTreeNode<int>>& tree, int low_range, int high_range){
  if(tree){
    if(tree->data < low_range || tree->data > high_range){
      return false;
    }
    return AreKeysInRange(tree->left, low_range, tree->data) && AreKeysInRange(tree->right, tree->data, high_range);
  }
  return true;
}

bool IsBinaryTreeBST(const unique_ptr<BinaryTreeNode<int>>& tree) {
  // TODO - you fill in here.
  return AreKeysInRange(tree, std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "is_tree_a_bst.cc", "is_tree_a_bst.tsv",
                         &IsBinaryTreeBST, DefaultComparator{}, param_names);
}
