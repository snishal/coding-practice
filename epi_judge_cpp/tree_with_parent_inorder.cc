#include <vector>

#include "binary_tree_with_parent_prototype.h"
#include "test_framework/generic_test.h"
using std::vector;

vector<int> InorderTraversal(const unique_ptr<BinaryTreeNode<int>>& tree) {
  // TODO - you fill in here.
  vector<int> traversal;
  const BinaryTreeNode<int> *curr = tree.get(), *prev = nullptr, *next = nullptr;

  while(curr){
    if(prev == curr->parent){
      if(curr->left){
        next = curr->left.get();
      }else{
        traversal.emplace_back(curr->data);
        next = curr->right ? curr->right.get() : curr->parent;
      }
    }else if(prev == curr->left.get()){
      traversal.emplace_back(curr->data);
      next = curr->right ? curr->right.get() : curr->parent;
    }else{
      next = curr->parent;
    }

    prev = curr;
    curr = next;
  }

  return traversal;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "tree_with_parent_inorder.cc",
                         "tree_with_parent_inorder.tsv", &InorderTraversal,
                         DefaultComparator{}, param_names);
}
