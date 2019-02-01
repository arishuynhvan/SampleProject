#include <chrono>
#include <iostream>
#include <sstream>
#include <string>
#include "SampleFunction.hpp"
#include "UnitTest++.h"

namespace  // blank namespace = file scope
{
typedef std::chrono::high_resolution_clock hrclock_t;

// Needed because at present mingw has not implemented this (C++11).
// Replace to_string with std::to_string when possible
template <typename T> std::string to_string(T duration)
{
  std::stringstream converter;
  converter << duration;
  return converter.str();
}

std::string TestTime(hrclock_t::time_point t1, hrclock_t::time_point t2)
{
  using namespace std::chrono;
  auto elapsed = duration_cast<nanoseconds>(t2 - t1).count();
  if (elapsed < 10000) return {to_string(elapsed) + "\t nsec for : "};
  elapsed = duration_cast<microseconds>(t2 - t1).count();
  if (elapsed < 10000) return {to_string(elapsed) + "\t usec for : "};
  elapsed = duration_cast<milliseconds>(t2 - t1).count();
  if (elapsed < 10000) return {to_string(elapsed) + "\t msec for : "};
  elapsed = duration_cast<seconds>(t2 - t1).count();
  return {to_string(elapsed) + "\t sec  for : "};
}
}  // blank namespace

SUITE(SampleFunction)  // Class or method name
{
TEST(SampleFunction_ExampleName)
{
  int x = 7;
  auto t1 = hrclock_t::now();  // Start time
  auto rc = SensitivityAnalysis::SampleFunction(x);
  auto t2 = hrclock_t::now();  // End time
  std::cout << TestTime(t1, t2) << "SampleFunction";
  std::cout << std::endl;

  CHECK_EQUAL(1, rc);
}
}  // suite SampleFunction

