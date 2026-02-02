#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "ray.h"

class Sphere : public Hittable {
  Point3 center;
  double radius;

public:
  Sphere(const Point3 &p, double radius)
      : center(p), radius(std::fmax(0, radius)) {}

  bool hit(const Ray &r, double r_tmin, double r_tmax,
           HitRecord &rec) const override {
    Vec3 oc = center - r.origin();
    auto a = r.direction().mod_sq();
    // auto b = -2.0 * dot(r.direction(), oc);
    auto h = dot(r.direction(), oc);
    auto c = oc.mod_sq() - radius * radius;

    auto discriminant = h * h - a * c;

    if (discriminant < 0)
      return false;

    auto sqrtd = std::sqrt(discriminant);
    auto root = (h - sqrtd) / a;

    if (root <= r_tmin || r_tmax <= root) {
      root = (h + sqrtd) / a;
      if (root <= r_tmin || r_tmax <= root)
        return false;
    }

    rec.t = root;
    rec.p = r.at(root);
    Vec3 outward_normal = (rec.p - center) / radius;
    rec.set_face_normal(r, outward_normal);

    return true;
  }
};

#endif // !SPHERE_H
