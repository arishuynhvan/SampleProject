#include <vector>
#include <stdexcept>
#include <cmath>
#include <cfloat>
#include "UnitTest++.h"
#include "LinearModel.hpp"
#include "logarithmicModel.hpp"
#include "FiniteDifference.hpp"

namespace SensitivityAnalysis
{
namespace UnitTests
{
SUITE(UnitTestFiniteDifference)
{
  //TODO unittest for all the return cases
  //TODO test for the exact values of minSC maxSC meanSC matrixSC for linear model when x{{1,2}}
  //TODO test all getters
TEST(LinearModel_ValidArguments)
{
  std::vector<std::vector<double>> x {{1.0,2.0,3.0,4.0,5.0}};
  std::vector<double> params {{1.0, 1.0}};
  double d = 0.01;
  Unfit::Examples::LinearModel lm;

  FiniteDifference fd;
  fd.calculateSensitivity(params, x,lm,d);
  auto meanSC = fd.getSCMean();
  CHECK_CLOSE(3.0,meanSC[0],0.05);
  CHECK_CLOSE(1.0, meanSC[1],0.05);
}
TEST(Invalid_d)
{
  std::vector<std::vector<double>> x {{1.0,2.0,3.0,4.0,5.0}};
  std::vector<double> params {{1.0, 1.0}};
  double d = 0.0;
  FiniteDifference fd;
  CHECK_EQUAL(1, fd.invalidArguments(params, x,d));
  d = NAN;
  CHECK_EQUAL(1, fd.invalidArguments(params, x,d));
  d = INFINITY;
  CHECK_EQUAL(1, fd.invalidArguments(params, x,d));
  d = 1e-16;
  CHECK_EQUAL(1, fd.invalidArguments(params, x,d));
}
TEST(Invalid_c)
{
  std::vector<std::vector<double>> x {{1.0,2.0,3.0,4.0,5.0}};
  std::vector<double> params {{INFINITY, 1.0}};
  double d = 0.01;
  FiniteDifference fd;
  CHECK_EQUAL(2, fd.invalidArguments(params, x,d));
  params[0]=NAN;
  CHECK_EQUAL(2, fd.invalidArguments(params, x,d));
  params[0]=0.0;
  CHECK_EQUAL(2, fd.invalidArguments(params, x,d));
  params[0]=std::nextafter(0.0,DBL_MIN);
  CHECK_EQUAL(2, fd.invalidArguments(params, x,d));
}
TEST(Invalid_x)
{
  std::vector<std::vector<double>> x {{NAN,2.0,3.0,4.0,5.0}};
  std::vector<double> params {{1.0, 1.0}};
  double d = 0.01;
  FiniteDifference fd;
  CHECK_EQUAL(3, fd.invalidArguments(params, x,d));
  x[0][0]=INFINITY;
  CHECK_EQUAL(3, fd.invalidArguments(params, x,d));
}
TEST(Invalid_outputs)
{
  std::vector<std::vector<double>> x {{-1.0,2.0,3.0,4.0,5.0}};
  std::vector<double> params {{1.0,1.0}};
  double d = 0.01;
  LogarithmicModel logm;
  FiniteDifference fd;
  CHECK_EQUAL(2, fd.calculateSensitivity(params, x,logm,d));
}
TEST(Valid_sdNormalize)
{
  std::vector<std::vector<double>> x {{1.0,2.0,3.0,4.0,5.0}};
  std::vector<double> params {{1.0, 1.0}};
  double d = 0.01;
  Unfit::Examples::LinearModel lm;
  std::vector<double> paramSD {{0.1,0.1}};
  double ySD {0.5};

  FiniteDifference fd;
  fd.calculateSensitivity(params, x,lm,d);
  fd.sdNormalize(paramSD,ySD);

  auto sdnSC = fd.getSDNSC();
  CHECK_CLOSE(0.6,sdnSC[0],0.05);
  CHECK_CLOSE(0.2, sdnSC[1],0.05);
}
TEST(Invalid_paramSD)
{
  std::vector<std::vector<double>> x {{1.0,2.0,3.0,4.0,5.0}};
  std::vector<double> params {{1.0, 1.0}};
  double d = 0.01;
  Unfit::Examples::LinearModel lm;
  std::vector<double> paramSD {{NAN, 1.0}};
  double ySD = 0.01;

  FiniteDifference fd;
  fd.calculateSensitivity(params, x,lm,d);
  CHECK_EQUAL(1, fd.sdNormalize(paramSD, ySD));
}
TEST(Invalid_ySD)
{
  std::vector<std::vector<double>> x {{1.0,2.0,3.0,4.0,5.0}};
  std::vector<double> params {{1.0, 1.0}};
  double d = 0.01;
  Unfit::Examples::LinearModel lm;
  std::vector<double> paramSD {{1.0, 1.0}};
  double ySD = 0.0;

  FiniteDifference fd;
  fd.calculateSensitivity(params, x,lm,d);
  CHECK_EQUAL(2, fd.sdNormalize(paramSD, ySD));
}
TEST(SDNormalize_when_calculateSensitivity_failed)
{
  std::vector<std::vector<double>> x {{1.0,2.0,3.0,4.0,5.0}};
  std::vector<double> params {{1.0, 1.0}};
  double d = 0.0;
  Unfit::Examples::LinearModel lm;
  std::vector<double> paramSD {{1.0, 1.0}};
  double ySD = 0.01;

  FiniteDifference fd;
  fd.calculateSensitivity(params, x,lm,d);
  CHECK_EQUAL(3, fd.sdNormalize(paramSD, ySD));
}
}  // suite UnitTestFiniteDifference
}  // namespace UnitTests
}  // namespace SensitivityAnalysis

