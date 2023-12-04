#ifndef FINDROUTEAPP_MODEL_ELLERSALGORITHM_H
#define FINDROUTEAPP_MODEL_ELLERSALGORITHM_H

#include "Data.h"

namespace frp {

class EllersAlgorithm {
 public:
  EllersAlgorithm(Data &);
  ~EllersAlgorithm() = default;

  std::vector<bool> get_right_walls();
  std::vector<bool> get_bottom_walls();

 private:
  int currentSet{1};
  Data &data_;
  std::vector<int> tmp_line_;

  std::vector<std::vector<bool>> rightWalls_;
  std::vector<std::vector<bool>> bottomWalls_;

  void GenerateMaze();
  void FillEmptyValue();
  void AssignUniqueSet();
  void AddingVerticalWalls(int);
  void MergeSet(int, int);
  void AddingHorizontalWalls(int);
  int CalculateUniqueSet(int);
  void CheckedHorizontalWalls(int);
  int CalculateHorizontalWalls(int, int);
  void PreparatingNewLine(int row);
  void AddingEndLine();
  void CheckedEndLine();
  bool RandomBool();

  void set_right_walls(int, int, bool);
  bool get_right_walls(int, int);
  bool get_bottom_walls(int, int);
  void set_bottom_walls(int, int, bool);

  void ResizeRightWalls();
  void ResizeBottomWalls();
  void ClearWalls();
};
}  //  namespace frp

#endif  // FINDROUTEAPP_MODEL_ELLERSALGORITHM_H
