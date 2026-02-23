#ifndef VEC3_H
#define VEC3_H

#include "raytracing.h"
#include <cmath>
#include <iostream>

#define MIN_F (1e-160)

class Vec3 {

public:
  double e[3];

  // Constructors
  Vec3() : e{0, 0, 0} {};
  Vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

  // Getters
  double x() const { return e[0]; }
  double y() const { return e[1]; }
  double z() const { return e[2]; }

  // prop
  double mod_sq() const { return (e[0] * e[0] + e[1] * e[1] + e[2] * e[2]); }
  double mod() const { return std::sqrt(mod_sq()); }

  // overloads
  Vec3 operator-() const { return Vec3(-e[0], -e[1], -e[2]); }
  double operator[](int i) const { return e[i]; }
  double &operator[](int i) { return e[i]; }

  Vec3 &operator+=(const Vec3 &v) {
    e[0] += v.e[0];
    e[1] += v.e[1];
    e[2] += v.e[2];
    return *this;
  }
  Vec3 &operator*=(double t) {
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;
    return *this;
  }
  Vec3 &operator/=(double t) { return *this *= (1 / t); }

  static Vec3 rand(double min = -1, double max = 1) {
    return Vec3(rand_d(min, max), rand_d(min, max), rand_d(min, max));
  }
};

using Point3 = Vec3;

// Utility fun
inline std::ostream &operator<<(std::ostream &out, const Vec3 &v) {
  return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline Vec3 operator+(const Vec3 &u, const Vec3 &v) {
  return Vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline Vec3 operator-(const Vec3 &u, const Vec3 &v) {
  return Vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline Vec3 operator*(const Vec3 &u, const Vec3 &v) {
  return Vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline Vec3 operator*(double t, const Vec3 &v) {
  return Vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline Vec3 operator*(const Vec3 &v, double t) { return t * v; }

inline Vec3 operator/(const Vec3 &v, double t) { return (1 / t) * v; }

inline double dot(const Vec3 &u, const Vec3 &v) {
  return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}

inline Vec3 cross(const Vec3 &u, const Vec3 &v) {
  return Vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
              u.e[2] * v.e[0] - u.e[0] * v.e[2],
              u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline Vec3 unit_vec(const Vec3 &v) { return v / v.mod(); }

inline Vec3 rand_unit_vec() {
  while (true) {
    auto p = Vec3::rand(-1, 1);
    auto len_sq = p.mod_sq();
    if (MIN_F < len_sq && len_sq <= 1)
      return p / sqrt(len_sq);
  }
}

inline Vec3 rand_on_hemeisphere(const Vec3 &normal) {
  Vec3 on_unit_sp = rand_unit_vec();
  if (dot(normal, on_unit_sp) > 0.0)
    return on_unit_sp;
  else
    return -on_unit_sp;
}

#endif // !VEC3_H
