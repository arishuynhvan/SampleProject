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
// System includes first, e.g. #include <cmath>
// User includes next, e.g. #include "DataFileReader.hpp"
// Note: your file name should match the function/class name

namespace SensitivityAnalysis
{
/**
 * This SA technique approximates the partial derivatives of the model outputs
 * with respect to
 *
 * Recommended use cases:
 *
 *
 * Usage:
 *
 *
 * \param    x Contains the initial guess for x (optional) on input. Contains
 *           the resulting solution vector on output.
 * \param    a A square matrix of size (n x n). The matrix should be
 *           symmetric and positive definite.
 * \param    b The right-hand-side vector.
 * \param    epsilon (optional) is the tolerance for the convergence.
 * \return   an error code, 0 means success, 1 signifies invalid input,
 *           2 signifies failure to converge.
 */
class   FiniteDifference : public GenericSensitivityAnalysis
{
public:

    std::vector<double> FiniteDifference::operator()(const std::vector<double> &c,
                                   const std::vector<std::vector<double>> &x,
                                   Unfit::GenericModel& model){}
    {

    }
    std::vector<double> FiniteDifference::getModelOutput(){

        return model(x);
    }
};
}  // namespace SensitivityAnalysis

#endif
