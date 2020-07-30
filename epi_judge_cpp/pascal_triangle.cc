#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
vector<vector<int>> GeneratePascalTriangle(int num_rows) {
  if(num_rows == 0)return {};
  vector<vector<int>> pascal_triangle;
  vector<int> curr_row;
  
  pascal_triangle.push_back({1});
  for(int i = 1; i < num_rows; i++){
    vector<int> curr_row;

    curr_row.emplace_back(pascal_triangle.back().front());
    for(int i = 0; i < pascal_triangle.back().size() - 1; i++){
      curr_row.emplace_back(pascal_triangle.back()[i] + pascal_triangle.back()[i + 1]);
    }
    curr_row.emplace_back(pascal_triangle.back().back());

    pascal_triangle.push_back(curr_row);
  }

  return pascal_triangle;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"num_rows"};
  return GenericTestMain(args, "pascal_triangle.cc", "pascal_triangle.tsv",
                         &GeneratePascalTriangle, DefaultComparator{},
                         param_names);
}
