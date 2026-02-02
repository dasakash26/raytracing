#include "interval.h"
#include "raytracing.h"

#include "color.h"
#include "hittable.h"
#include "hittable_list.h"
#include "ray.h"
#include "sphere.h"
#include "vec3.h"

Color ray_color(const Ray &r, const Hittable &world) {
  HitRecord rec;
  if (world.hit(r, Interval(0.001, infinity), rec)) {
    return (rec.normal + Color(1, 1, 1)) * 0.5;
  }

  Vec3 unit_dir = unit_vec(r.direction());
  auto t = 0.5 * (unit_dir.y() + 1.0);
  return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
}

int main() {
  using std::clog;
  using std::cout;

  // Img
  auto aspect_ratio = 2.0;
  int img_w = 400;
  int img_h = int(img_w / aspect_ratio);
  img_h = (img_h) ? img_h : 1; // atleast 1

  // world
  HittableList world;

  world.add(make_shared<Sphere>(Point3(0, 0.5, -2), 1));
  world.add(make_shared<Sphere>(Point3(0, 0, -1), 0.5));
  world.add(make_shared<Sphere>(Point3(0, -100.5, -1), 100));

  // Camera
  auto focal_len = 1.0;
  auto vh = 5.0;
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
    clog << "\r>> Scanlines remaining: " << img_h - j - 1 << ' ' << std::flush;
    for (int i = 0; i < img_w; ++i) {
      auto px_ij = px_00 + i * px_du + j * px_dv;
      auto ray_dir = px_ij - camera_center;

      Ray r(camera_center, ray_dir);

      Color px_clr = ray_color(r, world);
      write_color(cout, px_clr);
    }
  }

  clog << "\rDone.                       \n";

  return 0;
}
