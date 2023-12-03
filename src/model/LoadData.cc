#include "LoadData.h"

namespace frp {
LoadData::LoadData(Data &data) : data_(data) {}

void LoadData::ReadFile(const std::string &file_path) {
  std::ifstream in(file_path);
  if (!in.is_open()) {
    throw std::logic_error("File doesn't exist\n");
  }

  int rows, cols;
  if (!(in >> rows >> cols) || rows < 1 || cols < 1 || rows > 50 || cols > 50) {
    throw std::logic_error("Incorrect data in the file\n");
  }

  std::vector<bool> first_matrix(rows * cols), second_matrix(rows * cols);
  for (auto&& i:first_matrix) {
    int tmpInsert;
    if (!(in >> tmpInsert)) {
      throw std::logic_error("Incorrect data in the file\n");
    }
    i = tmpInsert;
  }

  for (auto&& i : second_matrix) {
    int tmpInsert;
    if (!(in >> tmpInsert)) {
      throw std::logic_error("Incorrect data in the file\n");
    }
    i = tmpInsert;
  }

  data_.set_rows(rows);
  data_.set_cols(cols);
  data_.set_horizontal_matrix(second_matrix);
  data_.set_vertical_matrix(first_matrix);
}

}  //  namespace frp
