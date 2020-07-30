#include <memory>

#include "bst_prototype_shared_ptr.h"
#include "test_framework/generic_test.h"
using std::shared_ptr;

shared_ptr<BstNode<int>> BST_TO_CLL(shared_ptr<BstNode<int>>& tree){
  if(tree == nullptr){
    return nullptr;
  }

  auto left_head = BST_TO_CLL(tree->left);
  auto right_head = BST_TO_CLL(tree->right);

  shared_ptr<BstNode<int>> left_tail = nullptr;
  if(left_head){
    left_tail = left_head->left;
    left_tail->right = tree;
    tree->left = left_tail;
    left_tail = tree;
  }else{
    left_head = left_tail = tree;
  }

  shared_ptr<BstNode<int>> right_tail = nullptr;
  if(right_head){
    right_tail = right_head->left;
    right_head->left = left_tail;
    left_tail->right = right_head;
  }else{
    right_tail = left_tail;
  }
  right_tail->right = left_head;
  left_head->left = right_tail;

  return left_head;
}

shared_ptr<BstNode<int>> BST_TO_DLL(shared_ptr<BstNode<int>> tree){
  auto head = BST_TO_CLL(tree);
  if(head){
    head->left->right = nullptr;
    head->left = nullptr;
  }
  return head;
}

int Length(shared_ptr<BstNode<int>> head){
  int length = 0;
  while(head){
    ++length, head = head->right;
  }

  return length;
}

void AppendNode(shared_ptr<BstNode<int>>* tail, shared_ptr<BstNode<int>>* node){
  (*tail)->right = *node;
  *tail = *node;
  *node = (*node)->right;
}

shared_ptr<BstNode<int>> MergeSortedDLL(shared_ptr<BstNode<int>> A, shared_ptr<BstNode<int>> B){
  shared_ptr<BstNode<int>> dummy_head = std::make_shared<BstNode<int>>(BstNode<int>{0});
  auto tail = dummy_head, it1 = A, it2 = B;
  while(it1 && it2){
    AppendNode(&tail, (it1->data < it2->data ? &it1 : &it2));
  }
  AppendNode(&tail, (it1 ? &it1 : &it2));

  return dummy_head->right;
}

shared_ptr<BstNode<int>> DLL_TO_BSTHelper(shared_ptr<BstNode<int>>* L, int s, int e){
  shared_ptr<BstNode<int>> root = nullptr;
  if(s < e){
    int m = s + ((e - s) / 2);
    auto left = DLL_TO_BSTHelper(L, s, m);
    root = *L;
    root->left = left;
    (*L) = (*L)->right;
    auto right = DLL_TO_BSTHelper(L, m + 1, e);
    root->right = right;
  }
  return root;
}

shared_ptr<BstNode<int>> DLL_TO_BST(shared_ptr<BstNode<int>> head, int length){
  return DLL_TO_BSTHelper(&head, 0, length);
}

shared_ptr<BstNode<int>> MergeTwoBSTs(shared_ptr<BstNode<int>> A,
                                      shared_ptr<BstNode<int>> B) {
  // TODO - you fill in here.
  A = BST_TO_DLL(A), B = BST_TO_DLL(B);
  int A_length = Length(A), B_length = Length(B);
  return DLL_TO_BST(MergeSortedDLL(A, B), A_length + B_length);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "B"};
  return GenericTestMain(args, "bst_merge.cc", "bst_merge.tsv", &MergeTwoBSTs,
                         DefaultComparator{}, param_names);
}
