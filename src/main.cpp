#include "camera.h"
#include "raytracing.h"

#include "hittable_list.h"
#include "sphere.h"
#include "vec3.h"

int main() {
  HittableList world;
  world.add(make_shared<Sphere>(Point3(0, 0, -1), 0.5));
  world.add(make_shared<Sphere>(Point3(0, -100.5, -1), 100));
  world.add(make_shared<Sphere>(Point3(1, 0.5, -2), 1));

  Camera cam;
  cam.aspect_ratio = 16.0 / 9.0;
  cam.img_w = 400;
  cam.samples_p_px = 100;

  cam.render(world);

  return 0;
}
