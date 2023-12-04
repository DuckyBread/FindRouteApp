#include <gtest/gtest.h>

#include "../back/Data.h"
#include "../back/LoadData.h"

TEST(LoadDataTest, ReadValidFile) {
  std::string file_path = "models/test_10_10.txt";
  auto data = new frp::Data();
  frp::LoadData loadData(data);

  EXPECT_NO_THROW(loadData.ReadFile(file_path));
  ASSERT_EQ(10, data->get_cols());
  ASSERT_EQ(10, data->get_rows());
}

TEST(LoadDataTest, ReadInvalidFileNotExist) {
  std::string file_path = "nonexistent_file.txt";
  auto data = new frp::Data();
  frp::LoadData loadData(data);

  EXPECT_THROW(loadData.ReadFile(file_path), std::logic_error);
}

TEST(LoadDataTest, ReadInvalidFileFormat) {
  std::string file_path = "models/test_fail_6_6.txt";
  auto data = new frp::Data();
  frp::LoadData loadData(data);

  EXPECT_THROW(loadData.ReadFile(file_path), std::logic_error);
}

TEST(LoadDataTest, ReadInvalidFileData) {
  std::string file_path = "models/test_5_5.txt";
  auto data = new frp::Data();
  frp::LoadData loadData(data);

  EXPECT_THROW(loadData.ReadFile(file_path), std::logic_error);
}