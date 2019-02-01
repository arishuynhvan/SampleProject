#include <iostream>
#include "SensitivityAnalysis.hpp"
#include "SampleFunction.hpp"

/**
 * This file provides an example of how to use your project. It should not be
 * too long. 
 */
int main()
{
  int x = 4;
  auto rc = SensitivityAnalysis::SampleFunction(x);  
  std::cout << "Function return code is " << rc << std::endl;

  return 0;
}
