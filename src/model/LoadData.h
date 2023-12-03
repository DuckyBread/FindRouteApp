#ifndef FINDROUTEAPP_MODEL_LOADDATA_H
#define FINDROUTEAPP_MODEL_LOADDATA_H

#include <fstream>

#include "Data.h"

namespace frp {

class LoadData {
 public:
  LoadData(Data &);
  ~LoadData() = default;

  void ReadFile(const std::string &);

 private:
  Data &data_;
};

}  //  namespace frp

#endif  // FINDROUTEAPP_MODEL_LOADDATA_H
