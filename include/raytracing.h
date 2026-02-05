#ifndef RAYTRACING_H
#define RAYTRACING_H

#include <limits>
#include <memory>
#include <random>

// C++ Std Usings
using std::make_shared;
using std::shared_ptr;

// Constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions
inline double degrees_to_radians(double degrees) {
  return degrees * pi / 180.0;
}

inline double rand_d(double min = 0,
                     double max = 0.9999) { // !Dont read in hindi
  static std::mt19937 generator;
  std::uniform_real_distribution<double> distribution(min, max);
  return distribution(generator);
}

#endif // !RAYTRACING_H
