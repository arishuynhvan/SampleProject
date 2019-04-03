#include <vector>
#include <stdexcept>
#include <limits>
#include "UnitTest++.h"
#include "LinearModel.hpp"
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
TEST(LinearModel_AllArgumentsValid)
{
  std::vector<std::vector<double>> x {{0.498531, 0.622145, 0.746551, 0.899687,
  0.995019, 1.24803, 1.49695, 1.7464, 1.86737, 1.92478, 2.07206, 2.12789,
  2.23212}};
  std::vector<double> params {{12.0, 1.0}};
  double d = 0.01;
  Unfit::Examples::LinearModel lm;

  FiniteDifference fd;
  fd.calculateSensitivity(params, x,lm,d);
  auto minSC = fd.getSCMin();
  auto maxSC = fd.getSCMax();
  auto meanSC = fd.getSCMean();
  CHECK(meanSC[0]> meanSC[1]);
  CHECK_EQUAL(meanSC.size(), params.size());
  CHECK_EQUAL(minSC.size(), params.size());
  CHECK_EQUAL(maxSC.size(), params.size());
}
TEST(ZeroDifference)
{
  std::vector<std::vector<double>> x {{0.498531, 0.622145, 0.746551, 0.899687,
  0.995019, 1.24803, 1.49695, 1.7464, 1.86737, 1.92478, 2.07206, 2.12789,
  2.23212}};
  std::vector<double> params {{12.0, 1.0}};
  double d = 0.0;
  Unfit::Examples::LinearModel lm;
  FiniteDifference fd;
  CHECK_THROW(fd.calculateSensitivity(params, x,lm,d), std::runtime_error);
}
TEST(InfiniteOutputs)
{
  std::vector<std::vector<double>> x {{-std::numeric_limits<double>::infinity(), 0.622145, 0.746551, 0.899687,
  0.995019, 1.24803, 1.49695, 1.7464, 1.86737, 1.92478, 2.07206, 2.12789,
  std::numeric_limits<double>::infinity()}};
  std::vector<double> params {{12.0, 1.0}};
  double d = 0.0;
  Unfit::Examples::LinearModel lm;
  FiniteDifference fd;
  CHECK_THROW(fd.calculateSensitivity(params, x,lm,d), std::runtime_error);
}
}  // suite UnitTestFiniteDifference
}  // namespace UnitTests
}  // namespace SensitivityAnalysis

