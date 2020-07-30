#include "list_node.h"
#include "test_framework/generic_test.h"

shared_ptr<ListNode<int>> AddTwoNumbers(shared_ptr<ListNode<int>> L1,
                                        shared_ptr<ListNode<int>> L2) {
  auto dummy_head = make_shared<ListNode<int>>(ListNode<int>{0, nullptr});
  auto iter = dummy_head;

  int carry = 0;
  while(L1 || L2 || carry){
    int sum = carry;
    if(L1){
      sum += L1->data;
      L1 = L1->next;
    }
    if(L2){
      sum += L2->data;
      L2 = L2->next;
    }

    carry = sum >= 10;
    sum %= 10;

    iter->next = make_shared<ListNode<int>>(ListNode<int>{sum, nullptr});
    iter = iter->next;
  }

  return dummy_head->next;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L1", "L2"};
  return GenericTestMain(args, "int_as_list_add.cc", "int_as_list_add.tsv",
                         &AddTwoNumbers, DefaultComparator{}, param_names);
}
