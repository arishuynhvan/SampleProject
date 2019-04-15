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
#include <stdexcept>
#include <cmath>
#include <cfloat>
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
  , doubleEps{}
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
     * \param   d A relative perturbation for all parameters, 0.01 of the nominal value by default
     * \return  0 -> success; 1 -> one or more arguments are invalid;
     *          2 -> output from the model contains infinity or nan
     */
    int FiniteDifference::calculateSensitivity(const std::vector<double> &c,
                    const std::vector<std::vector<double>> &x,
                    Unfit::GenericModel& model,
                    const double d)
    {
      if(FiniteDifference::invalidArguments(c,x,d)){return 1;}

      std::vector<double> scTmp;
      double derivative;
      std::vector<double> yHi;
      std::vector<double> yLow;
      auto cTmp=c;

      for (auto &param:cTmp)
      {
        auto tmp = param;
        param = tmp *(1+d);
        yHi = model(cTmp,x);
        param = tmp * (1-d);
        yLow = model(cTmp,x);
        doubleEps = 2*d*param;
        double scSumAbs = 0;
        double scTmpMin = DBL_MAX;
        double scTmpMax = -DBL_MIN;
        for(int i = 0u; i<yHi.size(); i++)
        {
          if(std::isinf(yHi[i]) || std::isnan(yHi[i])
             ||std::isinf(yLow[i])|| std::isnan(yLow[i])) {return 2;}
          derivative = (yHi[i]-yLow[i])/doubleEps;
          scTmp.push_back(derivative);
          if (derivative < scTmpMin)
          {
            scTmpMin = derivative;
          }
          if (derivative > scTmpMax)
          {
            scTmpMax = derivative;
          }
            scSumAbs += fabs(scTmp[i]);
          }
          scMin.push_back(scTmpMin);
          scMax.push_back(scTmpMax);
          scMatrix.push_back(scTmp);
          scMean.push_back(scSumAbs/yHi.size());
          //undo any perturbations for the current parameter before changing the next
          param = tmp;
          scTmp.clear();
      }
      return 0;
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
    //TODO doubleEps -> class variable; getDoubleEps for unittest
    double FiniteDifference::getDoubleEps(){
      return doubleEps;
    }

    /**
      * \return  0 -> success; 1 -> d is nan, infinity or <1e-15; 2 -> params contain nan, or 0 values;
      *          3 -> x contains infinity or nan
      */
    int FiniteDifference::invalidArguments(const std::vector<double> &c,
                    const std::vector<std::vector<double>> &x,
                    const double d) {
      if(!std::isnormal(d) || fabs(d)<1e-15){return 1;}
      for (auto &param:c){if(!std::isnormal(param)){return 2;}}
      for (auto &inputs:x){for(auto &input:inputs){if(std::isinf(input)||std::isnan(input)){return 3;}}}
      return 0;
    }
}
