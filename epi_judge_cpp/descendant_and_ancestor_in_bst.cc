#include <memory>

#include "bst_node.h"
#include "test_framework/binary_tree_utils.h"
#include "test_framework/generic_test.h"
#include "test_framework/timed_executor.h"
using std::unique_ptr;

bool FindFromNode(const unique_ptr<BstNode<int>>& node, const unique_ptr<BstNode<int>>& target){
  BstNode<int> *iter = node.get();
  while(iter && iter != target.get()){
    iter = (iter->data < target->data ? iter->right.get() : iter->left.get());
  }
  return iter == target.get();
}

bool PairIncludesAncestorAndDescendantOfM(
    const unique_ptr<BstNode<int>>& possible_anc_or_desc_0,
    const unique_ptr<BstNode<int>>& possible_anc_or_desc_1,
    const unique_ptr<BstNode<int>>& middle) {
  // TODO - you fill in here.
  BstNode<int> *iter0 = possible_anc_or_desc_0.get(), *iter1 = possible_anc_or_desc_1.get();
  while(iter0 != possible_anc_or_desc_1.get() && iter0 != middle.get() && iter1 != possible_anc_or_desc_0.get() && iter1 != middle.get() && (iter0 || iter1)){
    if(iter0){
      iter0 = (iter0->data < middle->data ? iter0->right.get() : iter0->left.get());
    }
    if(iter1){
      iter1 = (iter1->data < middle->data ? iter1->right.get() : iter1->left.get());
    }
  }

  if((iter0 != middle.get() && iter1 != middle.get()) || iter0 == possible_anc_or_desc_1.get() || iter1 == possible_anc_or_desc_0.get()){
    return false;
  }

  return FindFromNode(middle, iter0 == middle.get() ? possible_anc_or_desc_1 : possible_anc_or_desc_0);
}
bool PairIncludesAncestorAndDescendantOfMWrapper(
    TimedExecutor& executor, const unique_ptr<BstNode<int>>& tree,
    int possible_anc_or_desc_0, int possible_anc_or_desc_1, int middle) {
  auto& candidate0 = MustFindNode(tree, possible_anc_or_desc_0);
  auto& candidate1 = MustFindNode(tree, possible_anc_or_desc_1);
  auto& middle_node = MustFindNode(tree, middle);
  return executor.Run([&] {
    return PairIncludesAncestorAndDescendantOfM(candidate0, candidate1,
                                                middle_node);
  });
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "tree",
                                       "possible_anc_or_desc_0",
                                       "possible_anc_or_desc_1", "middle"};
  return GenericTestMain(args, "descendant_and_ancestor_in_bst.cc",
                         "descendant_and_ancestor_in_bst.tsv",
                         &PairIncludesAncestorAndDescendantOfMWrapper,
                         DefaultComparator{}, param_names);
}
