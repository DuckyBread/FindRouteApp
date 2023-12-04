#include "Maze.h"

namespace frp {
Maze::Maze(Data &data) : data_(data) {}

bool Maze::IsVisited(std::pair<int, int> cell) {
  if (!IsExist(cell)) {
    return true;
  }
  return used_[cell.first * data_.get_cols() + cell.second];
}

bool Maze::IsExist(std::pair<int, int> cell) {
  return cell.first > -1 && cell.first < data_.get_rows() && cell.second > -1 &&
         cell.second < data_.get_cols();
}

std::pair<bool, bool> Maze::IsWall(std::pair<int, int> cell) {
  return data_.IsWall(cell);
}

void Maze::FindRoute(std::pair<int, int> src, std::pair<int, int> dst) {
  if (!IsExist(src) || !IsExist(dst)) {
    throw std::logic_error("Incorrect coordinates!");
  }

  if (src == dst) {
    src_to_dst_route_.push(src.first * data_.get_cols() + src.second);
    throw std::logic_error("Same point!");
  }
  used_ = std::vector<bool>(data_.get_rows() * data_.get_cols(), false);
  src_to_dst_route_ = {};

  std::queue<std::pair<int, int>> queue_of_cells{{src}};
  used_[src.first * data_.get_cols() + src.second] = true;

  std::list<std::pair<std::pair<int, int>, std::queue<int>>> routes_to_cells;
  routes_to_cells.emplace_back(
      src, std::queue<int>({src.first * data_.get_cols() + src.second}));

  while (!queue_of_cells.empty()) {
    auto cell = queue_of_cells.front();
    queue_of_cells.pop();

    for (auto item : moves_) {
      std::pair<int, int> current_cell(cell.first + item.first,
                                       cell.second + item.second);
      if (!IsExist(current_cell) || IsVisited(current_cell)) {
        continue;
      }

      /* Check current cell for existing of wall */
      /* Move up, left, down, right */
      if ((item.first == -1 && IsWall(current_cell).second) ||
          (item.second == -1 && IsWall(current_cell).first) ||
          (item.first == 1 && IsWall(cell).second) ||
          (item.second == 1 && IsWall(cell).first))
        continue;

      queue_of_cells.emplace(current_cell);
      used_[(cell.first) * data_.get_cols() + cell.second] = true;

      auto find_elem_in_test = std::find_if(
          routes_to_cells.begin(), routes_to_cells.end(),
          [&cell](
              const std::pair<std::pair<int, int>, std::queue<int>> &element) {
            return element.first == cell;
          });
      std::queue<int> new_route = std::queue<int>(find_elem_in_test->second);
      new_route.push(current_cell.first * data_.get_cols() +
                     current_cell.second);
      routes_to_cells.emplace_back(current_cell, new_route);

      if (current_cell == dst) {
        src_to_dst_route_ = new_route;
        return;
      }
    }
  }
}

std::queue<int> &Maze::get_src_to_dst_route() { return src_to_dst_route_; }

}  //  namespace frp