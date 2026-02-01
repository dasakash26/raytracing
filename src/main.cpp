#include "color.h"
#include "ray.h"
#include "vec3.h"
#include <iostream>

using namespace std;

Color ray_color(const Ray &r) {
  Vec3 u_dir = unit_vec(r.direction());
  auto a = (u_dir.y() + 1.0) * 0.5;
  // LERP
  auto res = (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
  return res;
}

int main() {

  // Img
  auto aspect_ratio = 2.0;
  int img_w = 400;
  int img_h = int(img_w / aspect_ratio);
  img_h = (img_h) ? img_h : 1; // atleast 1

  // Camera
  auto focal_len = 1.0;
  auto vh = 2.0;
  auto vw = (double(img_w) / img_h) * vh; // real ar * vh
  auto camera_center = Point3(0, 0, 0);

  // Vectors: across the horizontal and down the vertical viewport edges
  auto vu = Vec3(vw, 0, 0);
  auto vv = Vec3(0, -vh, 0);

  // Vector: delta from px to px
  auto px_du = vu / img_w;
  auto px_dv = vv / img_h;

  // UL pixel
  auto vp_upper_left = camera_center - Vec3(0, 0, focal_len) - vu / 2 - vv / 2;
  auto px_00 = vp_upper_left + (px_du + px_dv) * 0.5; // center of ul px

  cout << "P3\n" << img_w << ' ' << img_h << "\n255\n";

  for (int j = 0; j < img_h; ++j) {
    clog << "\r>> Scanlines remaining: " << img_h - j - 1 << ' ' << flush;
    for (int i = 0; i < img_w; ++i) {
      auto px_ij = px_00 + i * px_du + j * px_dv;
      auto ray_dir = px_ij - camera_center;

      Ray r(camera_center, ray_dir);

      Color px_clr = ray_color(r);
      write_color(cout, px_clr);
    }
  }

  clog << "\rDone.                       \n";

  return 0;
}
