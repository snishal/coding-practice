#include "list_node.h"
#include "test_framework/generic_test.h"

shared_ptr<ListNode<int>> ReverseList(const shared_ptr<ListNode<int>>& head) {
  shared_ptr<ListNode<int>> prev = nullptr, curr = head;
  while (curr) {
    auto next = curr->next;
    curr->next = prev;
    prev = curr;
    curr = next;
  }
  return prev;
}

bool IsLinkedListAPalindrome(shared_ptr<ListNode<int>> L) {
  if(L == nullptr){
    return true;
  }

  auto slow = L, fast = L;
  while(fast && fast->next){
    slow = slow->next, fast = fast->next->next;
  }

  auto first_half_iter = L, second_half_iter = ReverseList(slow);
  while(first_half_iter && second_half_iter){
    if(first_half_iter->data != second_half_iter->data){
      return false;
    }
    first_half_iter = first_half_iter->next, second_half_iter = second_half_iter->next;
  }

  return true;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L"};
  return GenericTestMain(args, "is_list_palindromic.cc",
                         "is_list_palindromic.tsv", &IsLinkedListAPalindrome,
                         DefaultComparator{}, param_names);
}
