#include <gtest/gtest.h>

#include "../back/Data.h"
#include "../back/LoadData.h"
#include "../back/SaveData.h"

TEST(DataLoadSaveTest, SaveAndLoadValidData) {
  frp::Data dataOrigin, dataNew;
  frp::LoadData loadData(&dataOrigin);
  frp::SaveData saveData(&dataOrigin);

  std::string save_file_path = "tests/slave1_test.txt";
  std::string load_file_path = "models/test_10_10.txt";

  loadData.ReadFile(load_file_path);
  EXPECT_NO_THROW(saveData.SaveFile(save_file_path));

  loadData = frp::LoadData(&dataNew);
  EXPECT_NO_THROW(loadData.ReadFile(save_file_path));

  ASSERT_EQ(dataOrigin.get_cols(), dataNew.get_cols());
  ASSERT_EQ(dataOrigin.get_rows(), dataNew.get_rows());
  ASSERT_EQ(dataOrigin.get_maze(), dataNew.get_maze());
}

TEST(DataLoadSaveTest, SaveAndLoadEmptyData) {
  frp::Data dataOrigin, dataNew;
  frp::SaveData saveData(&dataOrigin);

  std::string save_file_path = "tests/slave2_test.txt";

  EXPECT_NO_THROW(saveData.SaveFile(save_file_path));

  frp::LoadData loadData = frp::LoadData(&dataNew);

  EXPECT_ANY_THROW(loadData.ReadFile(save_file_path));
}
