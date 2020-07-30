#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

double FindSalaryCap(int target_payroll, vector<int> current_salaries) {
  // TODO - you fill in here.
  std::sort(current_salaries.begin(), current_salaries.end());
  double unadjusted_salary_sum = 0.0;
  for(int i = 0; i < current_salaries.size(); ++i){
    const double adjusted_salaries_sum = current_salaries[i] * (current_salaries.size() - i);
    if(unadjusted_salary_sum + adjusted_salaries_sum >= target_payroll){
      return (target_payroll - unadjusted_salary_sum) / (current_salaries.size() - i);
    }
    unadjusted_salary_sum += current_salaries[i];
  }
  return -1.0;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"target_payroll", "current_salaries"};
  return GenericTestMain(args, "find_salary_threshold.cc",
                         "find_salary_threshold.tsv", &FindSalaryCap,
                         DefaultComparator{}, param_names);
}
