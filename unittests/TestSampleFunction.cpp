#include <vector>
#include "UnitTest++.h"
#include "LinearModel.hpp"
#include "FiniteDifference.hpp"

namespace SensitivityAnalysis
{
namespace UnitTests
{
SUITE(UnitTestFiniteDifference)
{
TEST(FiniteDifference_LinearModel_AllArgumentsValid)
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
  for (int i=0u; i<meanSC.size()-1; i++) {
    CHECK_CLOSE(meanSC[i], meanSC[i+1], 0.0001);
  }

}
}  // suite UnitTestFiniteDifference
}  // namespace UnitTests
}  // namespace SensitivityAnalysis

