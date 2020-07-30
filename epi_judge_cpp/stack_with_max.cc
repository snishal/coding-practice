#include <stdexcept>

#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
#include "test_framework/test_failure.h"
#include <stack>

using std::length_error;
using std::stack;

class Stack {
private:

  struct MaxCount{
    int element, count;
  };

  stack<int> elements;
  stack<MaxCount> maxCount;
public:
  bool Empty() const {
    return elements.empty();
  }
  int Max() const {
    if(Empty()){
      throw std::length_error("Max() : empty stack");
    }
    return maxCount.top().element;
  }
  int Pop() {
    if(Empty()){
      throw std::length_error("Max() : empty stack");
    }

    int top = elements.top();
    elements.pop();
    if(top == maxCount.top().element){
      int &frequency = maxCount.top().count;
      --frequency;
      if(frequency == 0){
        maxCount.pop();
      }
    }
    return top;
  }
  void Push(int x) {
    elements.push(x);
    if(maxCount.empty()){
      maxCount.push(MaxCount{x, 1});
    }else{
      auto curr_max = maxCount.top().element;
      if(x > curr_max){
        maxCount.push(MaxCount{x, 1});
      }else if(x == curr_max){
        int& frequency = maxCount.top().count;
        ++frequency;
      }
    }
  }
};
struct StackOp {
  std::string op;
  int argument;
};

namespace test_framework {
template <>
struct SerializationTrait<StackOp> : UserSerTrait<StackOp, std::string, int> {};
}  // namespace test_framework

void StackTester(const std::vector<StackOp>& ops) {
  try {
    Stack s;
    for (auto& x : ops) {
      if (x.op == "Stack") {
        continue;
      } else if (x.op == "push") {
        s.Push(x.argument);
      } else if (x.op == "pop") {
        int result = s.Pop();
        if (result != x.argument) {
          throw TestFailure("Pop: expected " + std::to_string(x.argument) +
                            ", got " + std::to_string(result));
        }
      } else if (x.op == "max") {
        int result = s.Max();
        if (result != x.argument) {
          throw TestFailure("Max: expected " + std::to_string(x.argument) +
                            ", got " + std::to_string(result));
        }
      } else if (x.op == "empty") {
        int result = s.Empty();
        if (result != x.argument) {
          throw TestFailure("Empty: expected " + std::to_string(x.argument) +
                            ", got " + std::to_string(result));
        }
      } else {
        throw std::runtime_error("Unsupported stack operation: " + x.op);
      }
    }
  } catch (length_error&) {
    throw TestFailure("Unexpected length_error exception");
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"ops"};
  return GenericTestMain(args, "stack_with_max.cc", "stack_with_max.tsv",
                         &StackTester, DefaultComparator{}, param_names);
}
