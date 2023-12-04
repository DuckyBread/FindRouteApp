#include <gtest/gtest.h>

#include "../back/Data.h"

TEST(DataTest, SetColsValid) {
  frp::Data data;

  EXPECT_NO_THROW(data.set_cols(10));
  EXPECT_EQ(data.get_cols(), 10);
}

TEST(DataTest, SetColsInvalid) {
  frp::Data data;

  EXPECT_THROW(data.set_cols(0), std::logic_error);
  EXPECT_THROW(data.set_cols(51), std::logic_error);
}

TEST(DataTest, SetRowsValid) {
  frp::Data data;

  EXPECT_NO_THROW(data.set_rows(20));
  EXPECT_EQ(data.get_rows(), 20);
}

TEST(DataTest, SetRowsInvalid) {
  frp::Data data;

  EXPECT_THROW(data.set_rows(0), std::logic_error);
  EXPECT_THROW(data.set_rows(51), std::logic_error);
}

TEST(DataTest, SetVerticalMatrix) {
  frp::Data data;
  std::vector<bool> vertical = {true, false, true, false};
  data.set_vertical_matrix(vertical);

  EXPECT_EQ(data.get_vertical_matrix(), vertical);
}

TEST(DataTest, SetHorizontalMatrix) {
  frp::Data data;
  std::vector<bool> horizontal = {false, true, false, true};
  data.set_horizontal_matrix(horizontal);

  EXPECT_EQ(data.get_horizontal_matrix(), horizontal);
}

TEST(DataTest, IsWall) {
  frp::Data data;

  std::vector<bool> vertical = {true, false, true, false};
  std::vector<bool> horizontal = {false, true, false, true};
  data.set_vertical_matrix(vertical);
  data.set_horizontal_matrix(horizontal);

  std::pair<int, int> cell{1, 1};  // Assuming a 2x2 matrix
  std::pair<bool, bool> walls = data.IsWall(cell);

  EXPECT_EQ(walls.first, false);  // Vertical wall at (1,1) should be false
  EXPECT_EQ(walls.second, true);  // Horizontal wall at (1,1) should be true
}

TEST(DataTest, GetMaze) {
  frp::Data data;

  std::vector<bool> vertical = {true, false, true, false};
  std::vector<bool> horizontal = {false, true, false, true};
  data.set_vertical_matrix(vertical);
  data.set_horizontal_matrix(horizontal);

  auto maze = data.get_maze();
  EXPECT_EQ(maze.first, vertical);
  EXPECT_EQ(maze.second, horizontal);
}

TEST(DataTest, GetVerticalMatrix) {
  frp::Data data;

  std::vector<bool> vertical = {true, false, true, false};
  data.set_vertical_matrix(vertical);

  EXPECT_EQ(data.get_vertical_matrix(), vertical);
}

TEST(DataTest, GetHorizontalMatrix) {
  frp::Data data;

  std::vector<bool> horizontal = {false, true, false, true};
  data.set_horizontal_matrix(horizontal);

  EXPECT_EQ(data.get_horizontal_matrix(), horizontal);
}
