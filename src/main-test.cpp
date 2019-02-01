#include "UnitTest++.h"
#include "UnitTestCustomUtilities.hpp"

// This file should not be changed, apart from to change the subset of the
// tests/suites that you want to run

int main()
{
  return UnitTest::RunAllTheTests();

  // to run only one suite, uncomment the following line
  // and specify the name of the suite. Also, comment out the RunAllTheTests()
  // return UnitTest::RunOneSuite("suite_name");

  // to run only one test, uncomment the following line
  // and specify the name of the test.Also, comment out the RunAllTheTests()
  // return UnitTest::RunOneTest("test_name");

  // to run multiple suites, uncomment the following line
  // and specify the names of the suites. Also, comment out the RunAllTheTests()
  // return UnitTest::RunMultipleSuites(suite_names);

  // to run multiple tests, uncomment the following line
  // and specify the names of the tests. Also, comment out the RunAllTheTests()
  // return UnitTest::RunMultipleTests(test_names);
}
