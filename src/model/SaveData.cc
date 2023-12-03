#include "SaveData.h"

namespace frp {
SaveData::SaveData(Data &data) : data_(data) {}

void SaveData::SaveFile(std::string FileName) {
  std::ofstream MyFile(FileName);
  MyFile << data_.get_cols() << " " << data_.get_rows() << '\n';

  auto tmpVector = data_.get_vertical_matrix();
  for (size_t i = 0; i < tmpVector.size(); ++i) {
    if (i == 0) {
      MyFile << tmpVector[i];
      continue;
    }
    MyFile << (i % data_.get_cols() == 0 ? '\n' : ' ') << tmpVector[i];
  }
  MyFile << std::endl << std::endl;

  tmpVector = data_.get_horizontal_matrix();
  for (size_t i = 0; i < tmpVector.size(); ++i) {
    if (i == 0) {
      MyFile << tmpVector[i];
      continue;
    }
    MyFile << (i % data_.get_cols() == 0 ? '\n' : ' ') << tmpVector[i];
  }
}

}  //  namespace frp