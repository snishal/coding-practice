#include <bits/stdc++.h>

#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
using std::vector;
using std::unordered_map;
using std::pair;

struct Point {
  int x, y;
};

int FindLineWithMostPoints(const vector<Point>& points) {
  struct HashPair{
    size_t operator() (const pair<int, int>& p) const{
      return std::hash<int>()(p.first) ^ std::hash<int>()(p.second);
    }
  };

  int maxPoints = 0;
  
  for(int i = 0; i < points.size(); i++){
    unordered_map<pair<int, int>, int, HashPair> slopeTable;
    int overlapping_points = 1;
    for(int j = i + 1; j < points.size(); j++){
      if(points[j].x == points[i].x && points[j].y == points[i].y){
        overlapping_points++;
      }else{
        int x_diff = points[j].x - points[i].x, y_diff = points[j].y - points[i].y;
        if(x_diff == 0){
          slopeTable[{1, 0}]++;
        }else{
          int gcd = std::__gcd(abs(x_diff), abs(y_diff));
          x_diff /= gcd, y_diff /= gcd;
          if(x_diff < 0){
            x_diff = -x_diff, y_diff = -y_diff;
          }
          slopeTable[{y_diff, x_diff}]++;
        }
      }
    }

    maxPoints = std::max(maxPoints, overlapping_points + (slopeTable.empty() ? 0 : std::max_element(slopeTable.begin(), slopeTable.end()
                                                                                              , [](const auto& lhs, const auto& rhs){
                                                                                                return lhs.second < rhs.second;
                                                                                              })->second));
  }

  return maxPoints;
}
namespace test_framework {
template <>
struct SerializationTrait<Point> : UserSerTrait<Point, int, int> {};
}  // namespace test_framework
bool operator==(const Point& lhs, const Point& rhs) {
  return std::tie(lhs.x, lhs.y) == std::tie(rhs.x, rhs.y);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"points"};
  return GenericTestMain(
      args, "line_through_most_points.cc", "line_through_most_points.tsv",
      &FindLineWithMostPoints, DefaultComparator{}, param_names);
}
