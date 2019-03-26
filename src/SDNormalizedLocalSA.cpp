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
#include "SDNormalizedLocalSA.hpp"
#include "FiniteDifference.hpp"

namespace SensitivityAnalysis
{
// Default construtor: keep Reset in sync with this if you change it
    SDNormalizedLocalSA::SDNormalizedLocalSA()
    : scMatrix {}
    , scMax {}
    , scMin {}
    , scMean{}
    , delta {0.01}
    {}

    SDNormalizedLocalSA::~SDNormalizedLocalSA() = default;

    /**
     * This SA technique quantifies the sensitivity of model's parameters
     * by slightly changing one factor at a time by a fixed percentage
     * and keeping all other factors constant. The results are then normalized
     * with the standard deviations of the parameters and the model's outputs.
     *
     * sc[i] = (paramSD[i]/ySD)*(y(c[i]*(1+delta))-y(c[i]*(1-delta)))/(2*delta*c[i])
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

    void SDNormalizedLocalSA::calculateSensitivity(const std::vector<double> &params,
                    const std::vector<std::vector<double>> &x,
                    Unfit::GenericModel& model,
                    const std::vector<double> &paramSD,
                    const double& ySD,
                    const double& d)
    {
        for (auto& param: params){
            FiniteDifference fd;
            fd.calculateSensitivity(param, x, model, d);
            meanSC = fd.getSCMean();
            minSC = fd.getSCMin();
            maxSC = fd.getSCMax();
            for(int i=0; i<params.size();i++){
                auto sdNormalized = paramSD[i]/ySD;
                scMax.push_back(sdNormalized*maxSC[i]);
                scMin.push_back(sdNormalized*minSC[i]);
                scMean.push_back(sdNormalized*meanSC[i])
            }
        }

    }
    std::vector<double> SDNormalizedLocalSA::getSCMax(){
        return scMax;
    }
    std::vector<double> SDNormalizedLocalSA::getSCMin(){
        return scMin;
    }
    std::vector<double> SDNormalizedLocalSA::getSCMean(){
        return scMean;
    }

    /**
     * getSCMatrix()[i] includes all sensitivity coefficients
     * calculated over the range of independent variables x
     * when parameter c[i] is perturbed
     */
    std::vector<std::vector<double>> SDNormalizedLocalSA::getSCMatrix(){
        return scMatrix;
    }
}
