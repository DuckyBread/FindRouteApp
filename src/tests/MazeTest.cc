#include <gtest/gtest.h>

#include "../back/Data.h"
#include "../back/LoadData.h"
#include "../back/Maze.h"

TEST(MazeTest, FindValidRoute) {
    frp::Data data;
    frp::LoadData loadData{&data};
    frp::Maze maze{&data};

    loadData.ReadFile("models/test_10_10.txt");
    std::pair<int, int> src = {0, 0};
    std::pair<int, int> dst = {2, 2};

    EXPECT_NO_THROW(maze.FindRoute(src, dst));
    EXPECT_FALSE(maze.get_src_to_dst_route().empty());
}

TEST(MazeTest, FindRouteIncorrectCoordinates) {
    frp::Data data;
    frp::LoadData loadData{&data};
    frp::Maze maze{&data};

    loadData.ReadFile("models/test_10_10.txt");
    std::pair<int, int> src = {-1, 0};
    std::pair<int, int> dst = {2, 2};

    EXPECT_THROW(maze.FindRoute(src, dst), std::logic_error);
}

TEST(MazeTest, FindRouteSameCoordinates) {
frp::Data data;
frp::LoadData loadData{&data};
frp::Maze maze{&data};

loadData.ReadFile("models/test_10_10.txt");
std::pair<int, int> src = {1, 1};
std::pair<int, int> dst = {1, 1};

EXPECT_THROW(maze.FindRoute(src, dst), std::logic_error);
}
