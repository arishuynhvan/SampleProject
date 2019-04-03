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
    std::vector<std::vector<double>> x {{0.498531, 0.622145, 0.746551, 0.899687,
      0.995019, 1.24803, 1.49695, 1.7464, 1.86737, 1.92478, 2.07206, 2.12789,
      2.23212}};
    std::vector<double> params {{5.0, 999.0}};
    double d = 0.0;
    Unfit::Examples::LinearModel lm;
    SensitivityAnalysis::FiniteDifference fd;
    fd.calculateSensitivity(params, x,lm,d);
    auto minSC = fd.getSCMin();
    auto maxSC = fd.getSCMax();
    auto meanSC = fd.getSCMean();
    std::cout <<"Sensitivity coefficient for linear model y="
    <<params[0] <<"x+" <<params[1] << "\n"
    <<std::setw(8)<<"Params"<<std::setw(20)<<' ' <<"MinSC"<<std::setw(20)<<' ' <<"MaxSC"<<std::setw(19)<<' '<<"MeanSC\n\n";

    for(int i =0u; i<params.size();i++){
        std::cout <<std::setw(8)<< params[i]<<std::setw(16)<<' '<<std::setw(9)<<minSC[i]<<std::setw(16)<<' '<<std::setw(9)<<maxSC[i] <<std::setw(16)<<' '<<std::setw(9)<<meanSC[i]<<"\n";
    }
    return 0;
}
