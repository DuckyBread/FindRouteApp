#ifndef FINDROUTEAPP_MODEL_MAZE_H
#define FINDROUTEAPP_MODEL_MAZE_H

#include <algorithm>
#include <list>
#include <queue>

#include "Data.h"

namespace frp {

class Maze {
 public:
  Maze(Data &);
  ~Maze() = default;

  void FindRoute(std::pair<int, int>, std::pair<int, int>);
  std::queue<int> &get_src_to_dst_route();

 private:
  Data &data_;
  std::vector<bool> used_{};
  std::queue<int> src_to_dst_route_{};
  const std::list<std::pair<int, int>> moves_{{0, -1}, {0, 1}, {-1, 0}, {1, 0}};

  bool IsVisited(std::pair<int, int>);
  bool IsExist(std::pair<int, int>);
  std::pair<bool, bool> IsWall(std::pair<int, int>);
};

}  // namespace frp

#endif  // FINDROUTEAPP_MODEL_MAZE_H
