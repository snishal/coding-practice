#include <vector>

#include "test_framework/fmt_print.h"
#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
using std::vector;

struct Rect {
  int left, right, height;
};
using Skyline = vector<Rect>;

Skyline ComputeSkyline(const vector<Rect>& buildings) {
  int min_left = std::numeric_limits<int>::max(),
    max_right = std::numeric_limits<int>::min();
  
  for(const Rect rectangle : buildings){
    min_left = std::min(min_left, rectangle.left);
    max_right = std::max(max_right, rectangle.right);
  }

  vector<int> height(max_right - min_left + 1, 0);
  for(const Rect rectangle : buildings){
    for(int i = rectangle.left; i <= rectangle.right; i++){
      height[i - min_left] = std::max(height[i - min_left], rectangle.height);
    }
  }

  Skyline result;
  int left = 0;
  for(int i = 1; i < height.size(); i++){
    if(height[i] != height[i - 1]){
      result.emplace_back(Rect{left + min_left, i - 1 + min_left, height[i - 1]});
      left = i;
    }
  }
  result.emplace_back(Rect{left + min_left, max_right, height.back()});

  return result;
}
bool operator==(const Rect& a, const Rect& b) {
  return a.left == b.left && a.right == b.right && a.height == b.height;
}

namespace test_framework {
template <>
struct SerializationTrait<Rect> : UserSerTrait<Rect, int, int, int> {};
}  // namespace test_framework

std::ostream& operator<<(std::ostream& out, const Rect& r) {
  return PrintTo(out, std::make_tuple(r.left, r.right, r.height));
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"buildings"};
  return GenericTestMain(args, "drawing_skyline.cc", "drawing_skyline.tsv",
                         &ComputeSkyline, DefaultComparator{}, param_names);
}
