#include <vector>
#include <set>

#include "test_framework/generic_test.h"
using std::vector;
using std::set;
// Solution 1
// vector<double> GenerateFirstKABSqrt2(int k) {
//   struct ABSqrt{
//     int a, b;
//     double val;
    
//     ABSqrt(int a, int b) : a(a), b(b), val(a + b * std::sqrt(2)) {}

//     bool operator< (const ABSqrt& that) const {
//       return val < that.val;
//     }
//   };

//   vector<double> result;
//   vector<ABSqrt> numbers;
//   int i = 0, j = 0;

//   numbers.emplace_back(ABSqrt{0, 0});
//   result.emplace_back(numbers.back().val);
//   for(int n = 1; n < k; n++){
//     ABSqrt a_plus_1(numbers[i].a + 1, numbers[i].b);
//     ABSqrt b_plus_1(numbers[j].a, numbers[j].b + 1);
    
//     numbers.emplace_back(std::min(a_plus_1, b_plus_1));
//     result.emplace_back(numbers.back().val);

//     if(a_plus_1.val == result.back()){
//       i++;
//     }
//     if(b_plus_1.val == result.back()){
//       j++;
//     }
//   }
//   return result;
// }

//Solution 2
vector<double> GenerateFirstKABSqrt2(int k) {
  struct ABSqrt{
    int a, b;
    double val;
    
    ABSqrt(int a, int b) : a(a), b(b), val(a + b * std::sqrt(2)) {}

    bool operator< (const ABSqrt& that) const {
      return val < that.val;
    }
  };

  vector<double> result;
  set<ABSqrt> numbers;

  numbers.emplace(ABSqrt{0, 0});
  while(result.size() < k){
    const auto min_num = numbers.cbegin();
    result.emplace_back(min_num->val);

    numbers.emplace(ABSqrt{min_num->a + 1, min_num->b});
    numbers.emplace(ABSqrt{min_num->a, min_num->b + 1});

    numbers.erase(numbers.cbegin());
  }
  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"k"};
  return GenericTestMain(args, "a_b_sqrt2.cc", "a_b_sqrt2.tsv",
                         &GenerateFirstKABSqrt2, DefaultComparator{},
                         param_names);
}
