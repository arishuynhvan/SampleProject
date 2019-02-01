#include "SampleFunction.hpp"
#include "UnitTest++.h"

namespace SensitivityAnalysis
{
namespace UnitTests
{
SUITE(UnitTestSampleFunction)
{
TEST(SampleFunction_TestName1)
{
  int x = 0;
  auto rc = SampleFunction(x);

  CHECK_EQUAL(0, rc);
}

TEST(SampleFunction_TestName2)
{
  int x = 1;
  auto rc = SampleFunction(x);

  CHECK_EQUAL(1, rc);
}
}  // suite UnitTestSampleFunction
}  // namespace UnitTests
}  // namespace SensitivityAnalysis
