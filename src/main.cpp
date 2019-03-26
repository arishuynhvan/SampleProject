#include <iostream>
#include <vector>
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
    std::vector<double> params {{12.0, 1.0}};
    double d = 0.01;
    Unfit::Examples::LinearModel lm;
    SensitivityAnalysis::FiniteDifference fd;
    fd.calculateSensitivity(params, x,lm,d);
    auto minSC = fd.getSCMin();
    auto maxSC = fd.getSCMax();
    auto meanSC = fd.getSCMean();
    std::cout <<"Sensitivity coefficient for linear model y="
    <<params[0] <<"x+" <<params[1] << "\n"
    <<"Params\tMinSC\t\tMaxSC\t\tMeanSC\n";

    for(int i =0u; i<params.size();i++){
        std::cout << params[i]<<"\t"<<minSC[i]<<"\t"<<maxSC[i] << "\t\t"<<meanSC[i]<<"\n";
    }
    return 0;
}
