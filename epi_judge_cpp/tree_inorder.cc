#include <memory>
#include <vector>
#include <stack>

#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;
using std::vector;
using std::stack;

vector<int> InorderTraversal(const unique_ptr<BinaryTreeNode<int>>& tree) {
  vector<int> traversal;
  stack<BinaryTreeNode<int>*> s;

  auto node = tree.get();

  while(node || !s.empty()){
    while(node){
      s.emplace(node);
      node = node->left.get();
    }

    node = s.top();
    s.pop();
    traversal.emplace_back(node->data);

    node = node->right.get();
  }

  return traversal;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "tree_inorder.cc", "tree_inorder.tsv",
                         &InorderTraversal, DefaultComparator{}, param_names);
}
