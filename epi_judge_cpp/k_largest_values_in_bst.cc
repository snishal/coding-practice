#include <memory>
#include <vector>

#include "bst_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;
using std::vector;

void Helper(const unique_ptr<BstNode<int>>& tree, int k, vector<int>& k_largest){
  if(tree && k_largest.size() < k){
    Helper(tree->right, k, k_largest);
    if(k_largest.size() < k){
      k_largest.emplace_back(tree->data);
      Helper(tree->left, k, k_largest);
    }
  }
}

vector<int> FindKLargestInBST(const unique_ptr<BstNode<int>>& tree, int k) {
  vector<int> k_largest;
  Helper(tree, k, k_largest);
  return k_largest;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree", "k"};
  return GenericTestMain(args, "k_largest_values_in_bst.cc",
                         "k_largest_values_in_bst.tsv", &FindKLargestInBST,
                         UnorderedComparator{}, param_names);
}
