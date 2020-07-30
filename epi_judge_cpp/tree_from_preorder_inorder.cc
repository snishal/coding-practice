#include <vector>
#include <unordered_map>

#include "binary_tree_node.h"
#include "test_framework/binary_tree_utils.h"
#include "test_framework/generic_test.h"
using std::vector;
using std::unordered_map;

unique_ptr<BinaryTreeNode<int>> Helper(const vector<int>& preorder, int l_pre, int r_pre, int l_in, int r_in, unordered_map<int, int>& inorder_idx){
  if(l_pre >= r_pre || l_in >= r_in){
    return nullptr;
  }
  
  int in_idx = inorder_idx[preorder[l_pre]];
  int left_tree_size = in_idx - l_in;

  return std::make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{
    preorder[l_pre],
    Helper(preorder, l_pre + 1, l_pre + 1 + left_tree_size, l_in, in_idx, inorder_idx),
    Helper(preorder, l_pre + 1 + left_tree_size, r_pre, in_idx + 1, r_in, inorder_idx)
  });
}

unique_ptr<BinaryTreeNode<int>> BinaryTreeFromPreorderInorder(
    const vector<int>& preorder, const vector<int>& inorder) {
  unordered_map<int, int> inorder_idx;
  for(int i = 0; i < inorder.size(); i++){
    inorder_idx[inorder[i]] = i;
  }

  return Helper(preorder, 0, preorder.size(), 0, inorder.size(), inorder_idx);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"preorder", "inorder"};
  return GenericTestMain(
      args, "tree_from_preorder_inorder.cc", "tree_from_preorder_inorder.tsv",
      &BinaryTreeFromPreorderInorder, DefaultComparator{}, param_names);
}
