#include <memory>

#include "list_node.h"
#include "test_framework/generic_test.h"
using std::shared_ptr;

shared_ptr<ListNode<int>> ReverseList(const shared_ptr<ListNode<int>>& L){
  shared_ptr<ListNode<int>> prev = nullptr, curr = L, next = nullptr;

  while(curr){
    next = curr->next;
    curr->next = prev;
    prev = curr;
    curr = next;
  }

  return prev;
}

shared_ptr<ListNode<int>> ZippingLinkedList(
    const shared_ptr<ListNode<int>>& L) {
  if(!L && !L->next){
    return L;
  }

  auto slow = L, fast = L;
  while(fast && fast->next){
    slow = slow->next;
    fast = fast->next->next;
  }

  auto first_half_head = L, second_half_head = slow->next;
  slow->next = nullptr;

  second_half_head = ReverseList(second_half_head);

  auto first_half_itr = first_half_head, second_half_itr = second_half_head;
  while (second_half_itr){
    auto first_half_next = first_half_itr->next, second_half_next = second_half_itr->next;
    
    first_half_itr->next = second_half_itr;
    second_half_itr->next = first_half_next;

    first_half_itr = first_half_next;
    second_half_itr = second_half_next;
  }
  

  return first_half_head;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L"};
  return GenericTestMain(args, "zip_list.cc", "zip_list.tsv",
                         &ZippingLinkedList, DefaultComparator{}, param_names);
}
