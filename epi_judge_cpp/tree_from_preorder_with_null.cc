#include <string>
#include <vector>

#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
#include "test_framework/timed_executor.h"
using std::string;
using std::vector;

unique_ptr<BinaryTreeNode<int>> Helper(const vector<int*>& preorder, int& i){
  if(i >= preorder.size() || preorder[i] == nullptr){
    ++i;
    return nullptr;
  }
  int key = *preorder[i++];
  auto left = Helper(preorder, i);
  auto right = Helper(preorder, i);

  return std::make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{
    key,
    std::move(left),
    std::move(right)
  });
}

unique_ptr<BinaryTreeNode<int>> ReconstructPreorder(
    const vector<int*>& preorder) {
  int i = 0;
  return Helper(preorder, i);
}
unique_ptr<BinaryTreeNode<int>> ReconstructPreorderWrapper(
    TimedExecutor& executor, const vector<string>& preorder) {
  vector<int> values;
  vector<int*> ptrs;
  values.reserve(preorder.size());
  for (auto& s : preorder) {
    if (s == "null") {
      ptrs.push_back(nullptr);
    } else {
      int i = std::stoi(s);
      values.push_back(i);
      ptrs.push_back(&values.back());
    }
  }

  return executor.Run([&] { return ReconstructPreorder(ptrs); });
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "preorder"};
  return GenericTestMain(args, "tree_from_preorder_with_null.cc",
                         "tree_from_preorder_with_null.tsv",
                         &ReconstructPreorderWrapper, DefaultComparator{},
                         param_names);
}
