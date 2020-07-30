#include <memory>

#include "list_node.h"
#include "test_framework/generic_test.h"
using std::shared_ptr;

shared_ptr<ListNode<int>> RemoveDuplicates(const shared_ptr<ListNode<int>>& L) {
  if(L == nullptr){
    return L;
  }
  auto prevUnique = L, curr = L->next;
  while(curr){
    if(curr->data != prevUnique->data){
      prevUnique->next = curr;
      prevUnique = curr;
    }
    curr = curr->next;
  }
  prevUnique->next = curr;
  
  return L;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L"};
  return GenericTestMain(args, "remove_duplicates_from_sorted_list.cc",
                         "remove_duplicates_from_sorted_list.tsv",
                         &RemoveDuplicates, DefaultComparator{}, param_names);
}
