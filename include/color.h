#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"

#define CLAMP 255.999

using Color = Vec3;

inline void write_color(std::ostream &out, const Color &pixel) {
  auto r = pixel.x();
  auto g = pixel.y();
  auto b = pixel.z();

  int rbyte = int(CLAMP * r);
  int gbyte = int(CLAMP * g);
  int bbyte = int(CLAMP * b);

  out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}
#endif // COLOR_H
