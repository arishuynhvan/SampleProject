// SensitivityAnalysis: a semi-automatic library for common SA methods
//
// Copyright (C) 2012- Dr Martin Buist & Dr Alberto Corrias
// Contacts: a0127826 _at_ u.nus.edu; martin.buist _at_ nus.edu.sg; alberto _at_ nus.edu.sg
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
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
#ifndef SENSITIVITYANALYSIS_INCLUDE_GENERICSENSITIVITYANALYSIS_HPP_
#define SENSITIVITYANALYSIS_INCLUDE_GENERICSENSITIVITYANALYSIS_HPP_


#include <vector>
#include "GenericModel.hpp"

namespace SensitivityAnalysis
{
/**
 * This class provides an interface to for any method in Sensitivity Analysis
 */
class GenericSensitivityAnalysis
{
 public:
  /**
   * As we are deriving from this class, the destructor should be virtual. The
   * default destructor is fine.
   */
  virtual ~GenericSensitivityAnalysis() = default;

  /**
   * All methods must be implemented using this interface. For details of what
   * constitutes a sensitivity analysis method please see the GenericSensitivityAnalysis
   * class documentation. Here we want to pass in a vector of parameters (c), and
   * a vector of vectors containing the independent variable values which will
   * be used to determine the outputs of the target model (x). x[0] will contain
   * a vector with the values of the first independent variable, x[1] will contain
   * the second, if present, etc. The method should then return a vector containing
   * the sensitivity coefficients for all the , i.e., y = f(x0, x1, ... , xN).
   *
   * \param c A vector of model parameters/constants
   * \param x A vector of vectors containing the values of independent variables,
   *          at which the model should be evaluated.
   * \param model A functor of a model
   */
  virtual void calculateSensitivity(const std::vector<double> &c,
      const std::vector<std::vector<double>> &x, Unfit::GenericModel& model)=0;
};

}  // namespace SensitivityAnalysis

#endif  // UNFIT_INCLUDE_SAMETHOD_HPP_

