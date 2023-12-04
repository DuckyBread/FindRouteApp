#include "DataTest.cc"
#include "EllersAlgorithmTest.cc"
#include "LoadDataTest.cc"
#include "MazeTest.cc"
#include "SaveDataTest.cc"

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
