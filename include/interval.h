#ifndef INTERNAL_H
#define INTERNAL_H

#include "raytracing.h"

class Interval {
public:
  double min, max;
  Interval() : max(+infinity), min(-infinity) {}
  Interval(double min, double max) : max(max), min(min) {}

  double size() const { return max - min; }

  bool contains(double x) const { return min <= x && x <= max; }

  bool surrounds(double x) const { return min < x && x < max; }

  static const Interval empty, universe;
};

inline const Interval Interval::empty = Interval(+infinity, -infinity);
inline const Interval Interval::universe = Interval(-infinity, +infinity);

#endif // !INTERNAL_H
