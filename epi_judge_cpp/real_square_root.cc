#include "test_framework/generic_test.h"

enum Ordering { Smaller, Equal, Larger};

Ordering Compare(double a, double b){
  double diff = (a - b) / std::max(std::abs(a), std::abs(b));
  return diff < -std::numeric_limits<double>::epsilon() 
          ? Ordering::Smaller 
          : diff > std::numeric_limits<double>::epsilon() ? Ordering::Larger : Ordering::Equal;
}

double SquareRoot(double x) {
  double left, right;
  if(x < 1.0){
    left = x, right = 1.0;
  }else{
    left = 1.0, right = x;
  }

  while (Compare(left, right) == Ordering::Smaller){
    double mid = left + 0.5 * (right - left);
    double midSq = mid * mid;
    if(Compare(midSq, x) == Ordering::Larger){
      right = mid;
    }else{
      left = mid;
    }
  }
  return left;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "real_square_root.cc", "real_square_root.tsv",
                         &SquareRoot, DefaultComparator{}, param_names);
}
