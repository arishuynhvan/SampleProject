#include <vector>
#include <stdexcept>
#include <cmath>
#include <cfloat>
#include "UnitTest++.h"
#include "LinearModel.hpp"
#include "logarithmicModel.hpp"
#include "SDNormalizedLocalSA.hpp"

namespace SensitivityAnalysis
{
namespace UnitTests
{
SUITE(UnitTestSDNormalizedLocalSA)
{
  //TODO unittest for all the return cases
  //TODO test for the exact values of minSC maxSC meanSC matrixSC for linear model when x{{1,2}}
  //TODO test all getters
TEST(LinearModel_ValidArguments)
{
  std::vector<std::vector<double>> x {{1.0,2.0,3.0,4.0,5.0}};
  std::vector<double> params {{1.0, 1.0}};
  std::vector<double> paramSD{{0.01,0.01}};
  double ySD=0.01;
  Unfit::Examples::LinearModel lm;

  SDNormalizedLocalSA sdn;
  sdn.calculateSensitivity(params, x,lm,paramSD, ySD);
  auto meanSC = sdn.getSCMean();
  CHECK_CLOSE(3.0,meanSC[0],0.05);
  CHECK_CLOSE(1.0, meanSC[1],0.05);
}
TEST(Invalid_paramSD)
{
  std::vector<std::vector<double>> x {{1.0,2.0,3.0,4.0,5.0}};
  std::vector<double> params {{1.0, 1.0}};
  std::vector<double> paramSD{{NAN,0.01}};
  double ySD=0.01;
  Unfit::Examples::LinearModel lm;

  SDNormalizedLocalSA sdn;
  CHECK_EQUAL(3, sdn.calculateSensitivity(params, x,lm,paramSD, ySD));
}
TEST(Invalid_ySD)
{
  std::vector<std::vector<double>> x {{1.0,2.0,3.0,4.0,5.0}};
  std::vector<double> params {{1.0, 1.0}};
  std::vector<double> paramSD{{0.01,0.01}};
  double ySD=0.0;
  Unfit::Examples::LinearModel lm;

  SDNormalizedLocalSA sdn;
  CHECK_EQUAL(4, sdn.calculateSensitivity(params, x,lm,paramSD, ySD));
}
}  // suite UnitTestSDNormalizedLocalSA
}  // namespace UnitTests
}  // namespace SensitivityAnalysis

