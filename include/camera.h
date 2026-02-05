#ifndef CAMERA_H
#include "color.h"
#include "hittable.h"
#include "ray.h"
#include "vec3.h"
#include <iostream>

class Camera {
  // Img
  int img_h;
  Point3 center, px_00;
  Vec3 px_du, px_dv;

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
  }

  Color ray_color(const Ray &r, const Hittable &world) {
    HitRecord rec;
    if (world.hit(r, Interval(0.001, infinity), rec)) {
      return (rec.normal + Color(1, 1, 1)) * 0.5;
    }

    Vec3 unit_dir = unit_vec(r.direction());
    auto t = 0.5 * (unit_dir.y() + 1.0);
    return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
  }

public:
  double aspect_ratio = 1.0;
  int img_w = 100;

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

        Ray r(center, ray_dir);

        Color px_clr = ray_color(r, world);
        write_color(cout, px_clr);
      }
    }

    clog << "\rDone.                       \n";
  }
};

#endif // !CAMERA_H
