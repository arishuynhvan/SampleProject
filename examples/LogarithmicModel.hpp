#ifndef LOGARITHMICMODEL_H
#define LOGARITHMICMODEL_H

#include <cmath>
#include <vector>
#include "GenericModel.hpp"

class LogarithmicModel : public Unfit::GenericModel
{
  public:
  std::vector<double> operator()(const std::vector<double> &c,
      const std::vector<std::vector<double>> &t)
  {
    auto model = t[0];
    for (auto &m : model){
      m = c[0]*log(c[1]*m);
    }
    return model;
  }
};

#endif // LOGARITHMICMODEL_H
