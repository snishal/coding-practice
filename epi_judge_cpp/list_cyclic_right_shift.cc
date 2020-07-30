#include <memory>

#include "list_node.h"
#include "test_framework/generic_test.h"
using std::shared_ptr;

shared_ptr<ListNode<int>> CyclicallyRightShiftList(shared_ptr<ListNode<int>> L,
                                                   int k) {
  if(L == nullptr){
    return nullptr;
  }

  int length = 1;
  auto tail = L;
  while(tail->next){
    length++, tail = tail->next;
  }

  k %= length;
  if(k == 0){
    return L;
  }

  tail->next = L;
  int step_to_head = length - k;
  auto new_tail = tail;

  while(step_to_head--){
    new_tail = new_tail->next;
  }
  auto new_head = new_tail->next;
  new_tail->next = nullptr;

  return new_head;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L", "k"};
  return GenericTestMain(
      args, "list_cyclic_right_shift.cc", "list_cyclic_right_shift.tsv",
      &CyclicallyRightShiftList, DefaultComparator{}, param_names);
}
