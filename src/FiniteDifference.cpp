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

#include <vector>
#include <math.h>
#include "GenericModel.hpp"
#include "GenericSensitivityAnalysis.hpp"
#include "FiniteDifference.hpp"

namespace SensitivityAnalysis
{
// Default construtor: keep Reset in sync with this if you change it
FiniteDifference::FiniteDifference()
  : scMatrix {}
  , scMax {}
  , scMin {}
  , scMean{}
  , delta {0.01}
{}

FiniteDifference::~FiniteDifference() = default;

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
    void FiniteDifference::calculateSensitivity(const std::vector<double> &c,
                    const std::vector<std::vector<double>> &x,
                    Unfit::GenericModel& model,
                    const double& d)
    {
        std::vector<double> scTmp;
        std::vector<double> yHi;
        std::vector<double> yLow;
        if(!d){
            delta=d;
        }
        auto cTmp=c;
        for (auto &param:cTmp){
            auto tmp = param;
            param = tmp *(1+delta);
            yHi = model(cTmp,x);
            param = tmp * (1-delta);
            yLow = model(cTmp,x);
            double doubleEps = 2*delta*param;
            double scTmpMax = (yHi[0]-yLow[0])/(doubleEps);
            double scTmpMin = scTmpMax;
            double scSumAbs = 0;
            for(int i = 0; i<yHi.size(); i++){
                scTmp.push_back((yHi[i]-yLow[i])/(doubleEps));
                if (scTmp[i] < scTmpMin){
                    scTmpMin = scTmp[i];
                }
                if (scTmp[i] > scTmpMax){
                    scTmpMax = scTmp[i];
                }
                scSumAbs += fabs(scTmp[i]);
            }
            scMin.push_back(scTmpMin);
            scMax.push_back(scTmpMax);
            scMatrix.push_back(scTmp);
            scMean.push_back(scSumAbs/yHi.size());
            //undo any perturbations for the current parameter before changing the next
            param = tmp;
        }
    }
    std::vector<double> FiniteDifference::getSCMax(){
        return scMax;
    }
    std::vector<double> FiniteDifference::getSCMin(){
        return scMin;
    }
    std::vector<double> FiniteDifference::getSCMean(){
        return scMean;
    }

    /**
     * getSCMatrix()[i] includes all sensitivity coefficients
     * calculated over the range of independent variables x
     * when parameter c[i] is perturbed
     */
    std::vector<std::vector<double>> FiniteDifference::getSCMatrix(){
        return scMatrix;
    }
}
