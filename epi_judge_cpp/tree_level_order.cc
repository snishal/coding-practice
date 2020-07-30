#include <memory>
#include <vector>
#include <queue>

#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;
using std::vector;
using std::queue;

vector<vector<int>> BinaryTreeDepthOrder(
    const unique_ptr<BinaryTreeNode<int>>& tree) {
  auto node = tree.get();
  queue<BinaryTreeNode<int>*> level;
  vector<vector<int>> levelTraversal;
  vector<int> levelNodes;

  if(node){
    level.emplace(node);
  }
  while(!level.empty()){
    auto levelSize = level.size();
    
    while(levelSize--){
      auto node = level.front();
      level.pop();

      levelNodes.emplace_back(node->data);
      if(node->left){
        level.emplace(node->left.get());
      }
      if(node->right){
        level.emplace(node->right.get());
      }
    }

    levelTraversal.emplace_back(levelNodes);
    levelNodes.clear();
  }

  return levelTraversal;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "tree_level_order.cc", "tree_level_order.tsv",
                         &BinaryTreeDepthOrder, DefaultComparator{},
                         param_names);
}
