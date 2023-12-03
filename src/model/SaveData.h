#ifndef FINDROUTEAPP_MODEL_SAVEDATA_H
#define FINDROUTEAPP_MODEL_SAVEDATA_H

#include <fstream>

#include "Data.h"

namespace frp {

class SaveData {
 public:
  SaveData(Data &);
  ~SaveData() = default;

  void SaveFile(std::string);

 private:
  Data &data_;
};

}  //  namespace frp

#endif  // FINDROUTEAPP_MODEL_SAVEDATA_H
