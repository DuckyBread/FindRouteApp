
#include "EllersAlgorithm.h"

namespace frp {
EllersAlgorithm::EllersAlgorithm(Data &data) : data_(data) {
  ClearWalls();
  ResizeBottomWalls();
  ResizeRightWalls();
  GenerateMaze();
}

void EllersAlgorithm::GenerateMaze() {
  FillEmptyValue();
  for (int j = 0; j < data_->get_rows() - 1; ++j) {
    AssignUniqueSet();
    AddingVerticalWalls(j);
    AddingHorizontalWalls(j);
    CheckedHorizontalWalls(j);
    PreparatingNewLine(j);
  }
  AddingEndLine();
}

void EllersAlgorithm::FillEmptyValue() {
  for (int i = 0; i < data_->get_cols(); ++i) {
    tmp_line_.push_back(false);
  }
}

void EllersAlgorithm::AssignUniqueSet() {
  for (int i = 0; i < data_->get_cols(); ++i) {
    if (tmp_line_.at(i) == false) {
      tmp_line_.at(i) = currentSet;
      ++currentSet;
    }
  }
}

void EllersAlgorithm::AddingVerticalWalls(int row) {
  for (int i = 0; i < data_.get_cols() - 1; ++i) {
    bool choice = RandomBool();
    if (choice || tmp_line_.at(i) == tmp_line_.at(i + 1)) {
      set_right_walls(row, i, true);
    } else {
      MergeSet(i, tmp_line_.at(i));
    }
  }
  set_right_walls(row, data_.get_cols() - 1, true);
}

void EllersAlgorithm::MergeSet(int index, int element) {
  int mutableSet = tmp_line_.at(index + 1);
  for (int j = 0; j < data_.get_cols(); ++j) {
    if (tmp_line_[j] == mutableSet) {
      tmp_line_[j] = element;
    }
  }
}

void EllersAlgorithm::AddingHorizontalWalls(int row) {
  for (int i = 0; i < data_.get_cols(); ++i) {
    bool choice = RandomBool();
    if (CalculateUniqueSet(tmp_line_[i]) != 1 && choice) {
      set_bottom_walls(row, i, true);
    }
  }
}

int EllersAlgorithm::CalculateUniqueSet(int element) {
  int countUniqSet = 0;
  for (int i = 0; i < data_.get_cols(); ++i) {
    if (tmp_line_[i] == element) {
      ++countUniqSet;
    }
  }
  return countUniqSet;
}

void EllersAlgorithm::CheckedHorizontalWalls(int row) {
  for (int i = 0; i < data_.get_cols(); ++i) {
    if (CalculateHorizontalWalls(tmp_line_[i], row) == 0) {
      set_bottom_walls(row, i, false);
    }
  }
}

int EllersAlgorithm::CalculateHorizontalWalls(int element, int row) {
  int countHorizontalWalls = 0;
  for (int i = 0; i < data_.get_cols(); ++i) {
    if (tmp_line_[i] == element && !get_bottom_walls(row, i)) {
      ++countHorizontalWalls;
    }
  }
  return countHorizontalWalls;
}

void EllersAlgorithm::PreparatingNewLine(int row) {
  for (int i = 0; i < data_.get_cols(); ++i) {
    if (get_bottom_walls(row, i)) {
      tmp_line_[i] = false;
    }
  }
}

void EllersAlgorithm::AddingEndLine() {
  AssignUniqueSet();
  AddingVerticalWalls(data_.get_rows() - 1);
  CheckedEndLine();
}

void EllersAlgorithm::CheckedEndLine() {
  for (int i = 0; i < data_.get_cols() - 1; ++i) {
    if (tmp_line_[i] != tmp_line_[i + 1]) {
      set_right_walls(data_.get_rows() - 1, i, false);
      MergeSet(i, tmp_line_[i]);
    }
    set_bottom_walls(data_.get_rows() - 1, i, true);
  }
  set_bottom_walls(data_.get_rows() - 1, data_.get_cols() - 1, true);
}

bool EllersAlgorithm::RandomBool() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, 1);
  return dis(gen) != 0;
}

std::vector<bool> EllersAlgorithm::get_right_walls() {
  std::vector<bool> tmp;
  for (const auto &subvector : rightWalls_) {
    tmp.insert(tmp.end(), subvector.begin(), subvector.end());
  }
  return tmp;
}

std::vector<bool> EllersAlgorithm::get_bottom_walls() {
  std::vector<bool> tmp;
  for (const auto &subvector : bottomWalls_) {
    tmp.insert(tmp.end(), subvector.begin(), subvector.end());
  }
  return tmp;
}

void EllersAlgorithm::ResizeRightWalls() {
  rightWalls_.resize(data_.get_rows());
  for (auto &row : rightWalls_) {
    row.resize(data_.get_cols());
  }
}

void EllersAlgorithm::ResizeBottomWalls() {
  bottomWalls_.resize(data_.get_rows());
  for (auto &row : bottomWalls_) {
    row.resize(data_.get_cols());
  }
}

bool EllersAlgorithm::get_right_walls(int row, int i) {
  return rightWalls_[row][i];
}

bool EllersAlgorithm::get_bottom_walls(int row, int i) {
  return bottomWalls_[row][i];
}

void EllersAlgorithm::set_right_walls(int row, int i, bool choice) {
  rightWalls_[row][i] = choice;
}

void EllersAlgorithm::set_bottom_walls(int row, int i, bool choice) {
  bottomWalls_[row][i] = choice;
}

void EllersAlgorithm::ClearWalls() {
  rightWalls_.clear();
  bottomWalls_.clear();
}

}  //  namespace frp
