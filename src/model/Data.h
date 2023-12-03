#ifndef FINDROUTEAPP_MODEL_DATA_H
#define FINDROUTEAPP_MODEL_DATA_H

#include <iostream>
#include <random>

namespace frp {

class Data {
 public:
  Data() = default;
  ~Data() = default;

  void set_cols(int);
  void set_rows(int);
  int get_cols() const;
  int get_rows() const;
  std::vector<bool> get_vertical_matrix();
  std::vector<bool> get_horizontal_matrix();

  void set_vertical_matrix(std::vector<bool>);
  void set_horizontal_matrix(std::vector<bool>);
  std::pair<std::vector<bool> &, std::vector<bool> &> get_maze();

  std::pair<bool, bool> IsWall(std::pair<int, int> &);

 private:
  std::vector<bool> vertical_matrix_;
  std::vector<bool> horizontal_matrix_;

  int rows_{0};
  int cols_{0};
};

}  //  namespace frp

#endif  // FINDROUTEAPP_MODEL_DATA_H
