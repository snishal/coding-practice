#include <istream>
#include <string>
#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::vector;
enum class Color { kWhite, kBlack };
struct Coordinate {
  bool operator==(const Coordinate& that) const {
    return x == that.x && y == that.y;
  }

  int x, y;
};

bool SearchMazeHelper(vector<vector<Color>>& maze, const Coordinate& s, const Coordinate& e, vector<Coordinate>& pathFollowed){
	
	if(s.x < 0 || s.x >= maze.size() || s.y < 0 || s.y >= maze[s.x].size() || maze[s.x][s.y] == Color::kBlack){
		return false;
	}
	
	if(s == e){
		pathFollowed.push_back(e);
		return true;
	}

	const Coordinate above = {s.x - 1, s.y};
	const Coordinate below = {s.x + 1, s.y};
	const Coordinate left = {s.x, s.y - 1};
	const Coordinate right = {s.x, s.y + 1};

	pathFollowed.push_back(s);
	maze[s.x][s.y] = Color::kBlack;
	
	if(SearchMazeHelper(maze, above, e, pathFollowed) || SearchMazeHelper(maze, below, e, pathFollowed) || SearchMazeHelper(maze, left, e, pathFollowed) || SearchMazeHelper(maze, right, e, pathFollowed)){
		return true;
	}

	// maze[s.x][s.y] = Color::kWhite; gets in infinite loop either don't change the color or keep visited to not repeat nodes
	pathFollowed.pop_back();

	return false;
}

vector<Coordinate> SearchMaze(vector<vector<Color>> maze, const Coordinate& s, const Coordinate& e) {
	vector<Coordinate> path;
	SearchMazeHelper(maze, s, e, path);
	return path;	
}

namespace test_framework {
template <>
struct SerializationTrait<Color> : SerializationTrait<int> {
  using serialization_type = Color;

  static serialization_type Parse(const json& json_object) {
    return static_cast<serialization_type>(
        SerializationTrait<int>::Parse(json_object));
  }
};
}  // namespace test_framework

namespace test_framework {
template <>
struct SerializationTrait<Coordinate> : UserSerTrait<Coordinate, int, int> {
  static std::vector<std::string> GetMetricNames(const std::string& arg_name) {
    return {};
  }

  static std::vector<int> GetMetrics(const Coordinate& x) { return {}; }
};
}  // namespace test_framework

bool PathElementIsFeasible(const vector<vector<Color>>& maze,
                           const Coordinate& prev, const Coordinate& cur) {
  if (!(0 <= cur.x && cur.x < maze.size() && 0 <= cur.y &&
        cur.y < maze[cur.x].size() && maze[cur.x][cur.y] == Color::kWhite)) {
    return false;
  }
  return cur == Coordinate{prev.x + 1, prev.y} ||
         cur == Coordinate{prev.x - 1, prev.y} ||
         cur == Coordinate{prev.x, prev.y + 1} ||
         cur == Coordinate{prev.x, prev.y - 1};
}

bool SearchMazeWrapper(TimedExecutor& executor,
                       const vector<vector<Color>>& maze, const Coordinate& s,
                       const Coordinate& e) {
  vector<vector<Color>> copy = maze;

  auto path = executor.Run([&] { return SearchMaze(copy, s, e); });

  if (path.empty()) {
    return s == e;
  }

  if (!(path.front() == s) || !(path.back() == e)) {
    throw TestFailure("Path doesn't lay between start and end points");
  }

  for (size_t i = 1; i < path.size(); i++) {
    if (!PathElementIsFeasible(maze, path[i - 1], path[i])) {
      throw TestFailure("Path contains invalid segments");
    }
  }

  return true;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "maze", "s", "e"};
  return GenericTestMain(args, "search_maze.cc", "search_maze.tsv",
                         &SearchMazeWrapper, DefaultComparator{}, param_names);
}
