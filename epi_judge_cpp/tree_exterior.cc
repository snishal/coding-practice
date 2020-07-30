#include <vector>

#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::vector;

void Boundary(const unique_ptr<BinaryTreeNode<int>>& node, vector<const unique_ptr<BinaryTreeNode<int>>*>& container, bool leftBoundary){
  if (node == nullptr ||
      (node->left == nullptr && node->right == nullptr)) {
    return;
  }

  if(leftBoundary){
    container.push_back(&node);
    if(node->left){
      Boundary(node->left, container, leftBoundary);
    }else{
      Boundary(node->right, container, leftBoundary);
    }
  }else{
    if(node->right){
      Boundary(node->right, container, leftBoundary);
    }else{
      Boundary(node->left, container, leftBoundary);
    }
    container.push_back(&node);
  }
}

void Leaves(const unique_ptr<BinaryTreeNode<int>>& node, vector<const unique_ptr<BinaryTreeNode<int>>*>& container){
  if(node != nullptr){
    if(node->left == nullptr && node->right == nullptr){
      container.push_back(&node);
    }else{
      Leaves(node->left, container);
      Leaves(node->right, container);
    }
  }
}

vector<const unique_ptr<BinaryTreeNode<int>>*> ExteriorBinaryTree(
    const unique_ptr<BinaryTreeNode<int>>& tree) {
  if(tree == nullptr){
    return {};
  }
  
  vector<const unique_ptr<BinaryTreeNode<int>>*> exterior{&tree};
  Boundary(tree->left, exterior, true);
  Leaves(tree->left, exterior);
  Leaves(tree->right, exterior);
  Boundary(tree->right, exterior, false);

  return exterior;
}
vector<int> CreateOutputVector(
    const vector<const unique_ptr<BinaryTreeNode<int>>*>& L) {
  if (std::find(std::begin(L), std::end(L), nullptr) != std::end(L)) {
    throw TestFailure("Resulting list contains nullptr");
  }
  std::vector<int> output;
  for (const auto* l : L) {
    output.push_back((*l)->data);
  }
  return output;
}

vector<int> ExteriorBinaryTreeWrapper(
    TimedExecutor& executor, const unique_ptr<BinaryTreeNode<int>>& tree) {
  auto result = executor.Run([&] { return ExteriorBinaryTree(tree); });

  return CreateOutputVector(result);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "tree"};
  return GenericTestMain(args, "tree_exterior.cc", "tree_exterior.tsv",
                         &ExteriorBinaryTreeWrapper, DefaultComparator{},
                         param_names);
}
