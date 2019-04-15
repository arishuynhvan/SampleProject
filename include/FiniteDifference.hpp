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
#include "GenericModel.hpp"
#include "GenericSensitivityAnalysis.hpp"
// System includes first, e.g. #include <cmath>
// User includes next, e.g. #include "DataFileReader.hpp"
// Note: your file name should match the function/class name

namespace SensitivityAnalysis
{
class FiniteDifference
{
 /**
   * The constructor sets all of the parameters to their default values.
   */
 public:
  FiniteDifference();

  /**
   * As we could derive from this class, the destructor should be virtual. In
   * this case the default destructor is just fine as we are putting everything
   * into std::vectors which take care of themselves.
   */
  virtual ~FiniteDifference();
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
    int calculateSensitivity(const std::vector<double> &c,
                    const std::vector<std::vector<double>> &x,
                    Unfit::GenericModel& model,
                    const double d=0.01);

    std::vector<double> getSCMax();
    std::vector<double> getSCMin();
    std::vector<double> getSCMean();

    /**
     * getSCMatrix()[i] includes all sensitivity coefficients
     * calculated over the range of independent variables x
     * when parameter c[i] is perturbed
     */
    std::vector<std::vector<double>> getSCMatrix();
    double getDoubleEps();

    /** Check if the arguments are valid
      *
      * \return  0 -> success; 1 -> d is nan, infinity or <1e-15; 2 -> params contain nan, or 0 values;
      *          3 -> x contains infinity or nan
      */
    int invalidArguments(const std::vector<double> &c,
                    const std::vector<std::vector<double>> &x,
                    const double d);

    /** This function normalizes sensitivity measure by the standard deviations
      * of the parameters and outputs
      *
      * \param paramSD A vector of standard deviations of all parameters (from data)
      * \param ySD The standard deviation of outputs (from data)
      * \return 0 -> success; 1 -> paramSD contains NAN, 2 -> invalid ySD;
      *         3 -> scMean is empty (i.e. calculateSensitivity() failed)
      */
    int sdNormalize (std::vector<double> paramSD, double ySD);
    std::vector<double> getSDNSC();


private:
    std::vector<std::vector<double>> scMatrix;
    std::vector<double> scMax;
    std::vector<double> scMin;
    std::vector<double> scMean;
    std::vector<double> sdnSC;
    double doubleEps;
};
}// namespace SensitivityAnalysis

#endif
