#include "binary_tree_node.h"
#include "test_framework/generic_test.h"

struct HeightBalanced{
  int height;
  bool balanced;
};

HeightBalanced CheckBalanced(const unique_ptr<BinaryTreeNode<int>>& tree) {
  if(tree == nullptr){
    return {0, true};
  }
  auto left = CheckBalanced(tree->left);
  if(!left.balanced){
    return {0, false};
  }
  auto right = CheckBalanced(tree->right);
  if(!right.balanced){
    return {0, false};
  }

  return {std::max(left.height, right.height) + 1, std::abs(left.height - right.height) <= 1};
}

bool IsBalanced(const unique_ptr<BinaryTreeNode<int>>& tree) {
  return CheckBalanced(tree).balanced;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "is_tree_balanced.cc", "is_tree_balanced.tsv",
                         &IsBalanced, DefaultComparator{}, param_names);
}
