#ifndef COLOR_H
#define COLOR_H

#include "interval.h"
#include "vec3.h"
#include <iostream>

using Color = Vec3;
using std::sqrt;

inline void write_color(std::ostream &out, const Color &pixel) {
  auto r = pixel.x();
  auto g = pixel.y();
  auto b = pixel.z();

  // gamma correction with gamma=2.0
  // r = sqrt(r);
  // g = sqrt(g);
  // b = sqrt(b);

  static const Interval intensity(0.000, 0.9999);

  int rbyte = int(256 * intensity.clamp(r));
  int gbyte = int(256 * intensity.clamp(g));
  int bbyte = int(256 * intensity.clamp(b));

  out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}
#endif // COLOR_H
