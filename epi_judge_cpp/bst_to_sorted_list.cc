#include <memory>
#include <vector>

#include "bst_prototype_shared_ptr.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::shared_ptr;

struct HeadTail{
  shared_ptr<BstNode<int>> head, tail;
};

HeadTail Helper(
    const shared_ptr<BstNode<int>>& node) {
  if(node == nullptr){
    return {nullptr, nullptr};
  }

  auto leftList = Helper(node->left);
  auto rightList = Helper(node->right);

  if(leftList.tail){
    leftList.tail->right = node;
  }
  node->left = leftList.tail;

  node->right = rightList.head;
  if(rightList.head){
    rightList.head->left = node;
  }

  return {leftList.head ? leftList.head : node, rightList.tail ? rightList.tail : noRde};
}

shared_ptr<BstNode<int>> BSTToDoublyLinkedList(
    const shared_ptr<BstNode<int>>& tree) {
  return Helper(tree).head;
}
std::vector<int> BSTToDoublyLinkedListWrapper(
    TimedExecutor& executor, const std::shared_ptr<BstNode<int>>& tree) {
  auto list = executor.Run([&] { return BSTToDoublyLinkedList(tree); });

  if (list && list->left) {
    throw TestFailure(
        "Function must return the head of the list. Left link must be null");
  }
  std::vector<int> v;
  while (list) {
    v.push_back(list->data);
    if (list->right && list->right->left != list) {
      throw TestFailure("List is ill-formed");
    }
    list = list->right;
  }
  return v;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "tree"};
  return GenericTestMain(
      args, "bst_to_sorted_list.cc", "bst_to_sorted_list.tsv",
      &BSTToDoublyLinkedListWrapper, DefaultComparator{}, param_names);
}
