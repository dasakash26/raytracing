#ifndef CAMERA_H

#include "color.h"
#include "hittable.h"
#include "ray.h"
#include "raytracing.h"
#include "vec3.h"
#include <iostream>

#define SQ_OFFSET 0.5
#define ABSORBPTION 0.5

class Camera {
  int img_h;
  Point3 center, px_00;    // center of: camera, Oth px
  Vec3 px_du, px_dv;       // Offset to px
  double px_samples_scale; // Color scale factor for a sum of pixel samples
  int max_depth = 50;      // Max ray bounce depth

  void init() {
    img_h = int(img_w / aspect_ratio);
    img_h = (img_h) ? img_h : 1; // atleast 1

    center = Point3(0, 0, 0);

    auto focal_len = 1.0;
    auto vh = 5.0;
    auto vw = (double(img_w) / img_h) * vh; // real ar * vh

    // Vectors: across the horizontal and down the vertical viewport edges
    auto vu = Vec3(vw, 0, 0);
    auto vv = Vec3(0, -vh, 0);

    // Vector: delta from px to px
    px_du = vu / img_w;
    px_dv = vv / img_h;

    auto vp_upper_left_px = center - Vec3(0, 0, focal_len) - vu / 2 - vv / 2;
    px_00 = vp_upper_left_px + (px_du + px_dv) * 0.5; // center of ul px

    px_samples_scale = 1.0 / samples_p_px;
  }

  Ray get_ray(int i, int j) const {
    auto offset = sample_sq();
    auto px_sample =
        px_00 + ((i + offset.x()) * px_du) + ((j + offset.y()) * px_dv);

    auto r_origin = center;
    auto r_dirn = px_sample - r_origin;

    return Ray(r_origin, r_dirn);
  }

  Vec3 sample_sq() const {
    return Vec3(rand_d() - SQ_OFFSET, rand_d() - SQ_OFFSET, 0);
  }

  Color ray_color(const Ray &r, int depth, const Hittable &world) {
    // lim ray bounce
    if (depth <= 0)
      return Color(0, 0, 0);

    HitRecord rec;
    if (world.hit(r, Interval(0.001, infinity), rec)) {
      Vec3 dirn = rec.normal + rand_on_hemeisphere(rec.normal);
      // return (rec.normal + Color(1, 1, 1)) * 0.5;
      // recursive call to simulate bouncing light
      // base case: when ray misses the obj
      return ABSORBPTION * ray_color(Ray(rec.p, dirn), depth - 1, world);
    }

    Vec3 unit_dir = unit_vec(r.direction());
    auto t = 0.5 * (unit_dir.y() + 1.0);
    return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
  }

public:
  double aspect_ratio = 1.0; // W:H
  int img_w = 100;
  int samples_p_px = 10; // Count of random samples for each pixel

  void render(const Hittable &world) {
    using std::clog;
    using std::cout;
    init();

    cout << "P3\n" << img_w << ' ' << img_h << "\n255\n";

    for (int j = 0; j < img_h; ++j) {
      clog << "\r>> Scanlines remaining: " << img_h - j - 1 << ' '
           << std::flush;
      for (int i = 0; i < img_w; ++i) {
        auto px_ij = px_00 + i * px_du + j * px_dv;
        auto ray_dir = px_ij - center;

        Color px_clr(0, 0, 0);
        for (int s = 0; s < samples_p_px; ++s) {
          Ray r = get_ray(i, j);
          px_clr += ray_color(r, max_depth, world);
        }

        write_color(cout, px_clr * px_samples_scale);
      }
    }

    clog << "\rDone.                       \n";
  }
};

#endif // !CAMERA_H
