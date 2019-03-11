// SensitivityAnalysis: a semi-automatic library for common SA methods
// Copyright (C) 2012- Dr Martin Buist & Dr Alberto Corrias
// Contacts: martin.buist _at_ nus.edu.sg; alberto _at_ nus.edu.sg
//
// See the 'Contributors' file for a list of those who have contributed
// to this work.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

#ifndef SENSITIVITYANALYSIS_INCLUDE_FINITEDIFFERENCE_HPP_
#define SENSITIVITYANALYSIS_INCLUDE_FINITEDIFFERENCE_HPP_

#include <vector>
#include "Unfit.hpp"
#include "GenericSensitivityAnalysis.hpp"
// System includes first, e.g. #include <cmath>
// User includes next, e.g. #include "DataFileReader.hpp"
// Note: your file name should match the function/class name

namespace SensitivityAnalysis
{
/**
 * This SA technique quantifies the partial derivative of model output
 * with respect to parameters by slightly changing one factor at a time
 * by a fixed percentage and keeping all other factors constant.
 *
 * dy/dc[i] = (y(c[i]*(1+delta))-y(c[i]*(1-delta)))/(2*delta*c[i])
 *
 * Recommended use cases:
 * All parameters have linear relationship with each other
 * The model is linear or additive, and deterministic.
 * It's often applied in the analysis of chemical kinetics
 * and molecular dynamics.
 *
 * Usage:
 *
 */
class   FiniteDifference : class GenericSensitivityAnalysis
{
public:

    /**
     * This SA technique quantifies the partial derivative of model output
     * with respect to parameters by slightly changing one factor at a time
     * by a fixed percentage and keeping all other factors constant.
     *
     * dy/dc[i] = (y(c[i]*(1+delta))-y(c[i]*(1-delta)))/(2*delta*c[i])
     *
     * Recommended use cases:
     * All parameters have linear relationship with each other
     * The model is linear or additive, and deterministic.
     * It's often applied in the analysis of chemical kinetics
     * and molecular dynamics.
     *
     * \param   c A vector of nominal values of parameters
     * \param   x A vector of independent variables. Each vector x[i] contains
     *          all possible values x[i][j] in the range of an independent variable
     * \param   model A functor of a model
     * \param   delta A relative perturbation for all parameters, 1% of each nominal value by default
     */
    void operator()(const std::vector<double> &c,
                            const std::vector<std::vector<double>> &x,
                            Unfit::GenericModel& model,
                            const double delta=0.01){}
    {
        std::vector<double> scTmp;
        std::vector<double> yHi;
        std::vector<double> yLow;
        auto cTmp=c;
        for (auto &param:cTmp){
            auto tmp = param;
            param = tmp *(1+delta);
            yHi = model(cTmp,x);
            param = tmp * (1-delta);
            yLow = model(cTmp,x);
            double scTmpMax = (yHi[i]-yLow[i])/(2*delta*param);
            double scTmpMin = scTmpMax;
            for(int i = 0; i<yHi.size(); i++){
                scTmp.push_back((yHi[i]-yLow[i])/(2*delta*param));
                if (scTmp[i] < scTmpMin){
                    scTmpMin = scTmp[i];
                }
                if (scTmp[i] > scTmpMax){
                    scTmpMax = scTmp[i];
                }
            }
            scMin.push_back(scTmpMin);
            scMin.push_back(scTmpMax);
            scMatrix.push_back(scTmp);
            param = tmp; //undo any perturbations for a parameter before changing the next
        }
    }
    std::vector<double> getSCMax{
        return scMax;
    }
    std::vector<double> getSCMin{
        return scMin;
    }
    /**
     * getSCMatrix()[i] includes all sensitivity coefficients
     * calculated over the range of independent variables x
     * when parameter c[i] is perturbed
     */
    std::vector<vector<double>> getSCMatrix(){
        return scMatrix;
    }
private:
    std::vector<std::vector<double>> scMatrix;
    std::vector<double> scMax;
    std::vector<double> scMin;

};
}  // namespace SensitivityAnalysis

#endif
