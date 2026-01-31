#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <ostream>

class Vec3 {
public:
  double e[3];

  // Constructors
  Vec3() : e{0, 0, 0} {};
  Vec3(double e0, double e1, double e2) {}

  // Getters
  double X() const { return e[0]; }
  double Y() const { return e[1]; }
  double Z() const { return e[2]; }

  // len
  double len_sq() const { return (e[0] * e[0] + e[0] * e[0]); }

  double len() const {}
  // overloads
};

#endif // !VEC3_H
