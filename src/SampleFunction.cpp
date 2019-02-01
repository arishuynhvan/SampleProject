#include "SampleFunction.hpp"

namespace SensitivityAnalysis
{
int SampleFunction(int x)
{
  if (x % 2 == 0) {  // x is even
    return 0;
  } else {           // x is odd
    return 1;
  }
}

}  // namespace SensitivityAnalysis
