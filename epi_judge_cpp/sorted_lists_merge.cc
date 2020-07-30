#include "list_node.h"
#include "test_framework/generic_test.h"

shared_ptr<ListNode<int>> appendNode(shared_ptr<ListNode<int>>* node, shared_ptr<ListNode<int>>* tail){
  (*tail)->next = *node;
  (*tail) = (*tail)->next;
  (*node) = (*node)->next;
}

shared_ptr<ListNode<int>> MergeTwoSortedLists(shared_ptr<ListNode<int>> L1, shared_ptr<ListNode<int>> L2) {
  shared_ptr<ListNode<int>> dummy_head = make_shared<ListNode<int>>(ListNode<int>{0}), tail = dummy_head;
  shared_ptr<ListNode<int>> it1 = L1, it2 = L2;

  while(it1 && it2){
    appendNode((it1->data < it2->data) ? &it1 : &it2, &tail);
  }

  tail->next = (it1) ? it1 : it2;

  return dummy_head->next;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L1", "L2"};
  return GenericTestMain(args, "sorted_lists_merge.cc",
                         "sorted_lists_merge.tsv", &MergeTwoSortedLists,
                         DefaultComparator{}, param_names);
}
