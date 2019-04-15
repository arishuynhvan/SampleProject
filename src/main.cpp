#include <iostream>
#include <vector>
#include <iomanip>
#include <stdexcept>
#include "SensitivityAnalysis.hpp"
#include "Unfit.hpp"
#include "LinearModel.hpp"
#include "FiniteDifference.hpp"

/**
 * This file provides an example of how to use your project.
 */
int main()
{
  std::vector<std::vector<double>> x {{1.0,5.0}};
  std::vector<double> params {{1.0, 1.0}};
  Unfit::Examples::LinearModel lm;
  SensitivityAnalysis::FiniteDifference fd;
  fd.calculateSensitivity(params, x,lm);
  auto minSC = fd.getSCMin();
  auto maxSC = fd.getSCMax();
  auto meanSC = fd.getSCMean();

  std::vector<double> paramSD {{0.1,0.1}};
  double ySD {0.5};
  fd.sdNormalize(paramSD, ySD);
  auto sdnSC = fd.getSDNSC();
  std::cout <<"Sensitivity coefficient for linear model y="
  <<params[0] <<"x+" <<params[1] << "\n"
  <<std::setw(8)<<"Params"<<std::setw(20)<<' ' <<"MinSC"
  <<std::setw(20)<<' ' <<"MaxSC"<<std::setw(19)<<' '<<"MeanSC"
  <<std::setw(19)<<' '<<"SD Normalized SC\n\n";

  for(int i =0u; i<params.size();i++){
      std::cout <<std::setw(8)<< params[i]<<std::setw(16)<<' '<<std::setw(9)
      <<minSC[i]<<std::setw(16)<<' '<<std::setw(9)<<maxSC[i] <<std::setw(16)<<' '<<std::setw(9)
      <<meanSC[i]<<std::setw(16)<<' '<<std::setw(9)<<sdnSC[i]<<"\n";
  }
  return 0;
}
