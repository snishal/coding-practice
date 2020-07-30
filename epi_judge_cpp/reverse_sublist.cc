#include "list_node.h"
#include "test_framework/generic_test.h"

shared_ptr<ListNode<int>> ReverseSublist(shared_ptr<ListNode<int>> L, int start,
                                         int finish) {
  shared_ptr<ListNode<int>> dummy_head = make_shared<ListNode<int>>(ListNode<int>{0, L});
  auto sub_list_head = dummy_head;

  int k = 1;
  while(k++ < start){
    sub_list_head = sub_list_head->next;
  }

  auto sub_list_iter = sub_list_head->next;
  while(start++ < finish){
    auto next = sub_list_iter->next;
    sub_list_iter->next = next->next;
    next->next = sub_list_head->next;
    sub_list_head->next = next;
  }

  return dummy_head->next;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L", "start", "finish"};
  return GenericTestMain(args, "reverse_sublist.cc", "reverse_sublist.tsv",
                         &ReverseSublist, DefaultComparator{}, param_names);
}
