#include "binary_tree_with_parent_prototype.h"
#include "test_framework/binary_tree_utils.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"

int getDepth(const unique_ptr<BinaryTreeNode<int>>& node){
	BinaryTreeNode<int> *currNode = node.get();
	int depth = 0;

	while(currNode){
		depth++;
		currNode = currNode->parent;
	}

	return depth;
}

BinaryTreeNode<int>* Lca(const unique_ptr<BinaryTreeNode<int>>& node0,
                         const unique_ptr<BinaryTreeNode<int>>& node1) {
  BinaryTreeNode<int> *n0 = node0.get(), *n1 = node1.get();
	int d1 = getDepth(node0), d2 = getDepth(node1);

	while(d1 > d2){
		n0 = n0->parent;
		d1--;
	}

	while(d2 > d1){
		n1 = n1->parent;
		d2--;
	}

	while(n0 && n1 && n0 != n1){
		n0 = n0->parent;
		n1 = n1->parent;
	}

  return n0;
}
int LcaWrapper(TimedExecutor& executor,
               const unique_ptr<BinaryTreeNode<int>>& tree, int key0,
               int key1) {
  const unique_ptr<BinaryTreeNode<int>>& node0 = MustFindNode(tree, key0);
  const unique_ptr<BinaryTreeNode<int>>& node1 = MustFindNode(tree, key1);

  auto result = executor.Run([&] { return Lca(node0, node1); });

  if (!result) {
    throw TestFailure("Result can not be nullptr");
  }
  return result->data;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "tree", "key0", "key1"};
  return GenericTestMain(args, "lowest_common_ancestor_with_parent.cc",
                         "lowest_common_ancestor.tsv", &LcaWrapper,
                         DefaultComparator{}, param_names);
}
