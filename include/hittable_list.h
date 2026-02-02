#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"
#include <memory>
#include <vector>

using std::make_shared;
using std::shared_ptr;

class HittableList : public Hittable {
public:
  std::vector<shared_ptr<Hittable>> objects;

  HittableList() {}
  HittableList(shared_ptr<Hittable> object) { add(object); }

  void add(shared_ptr<Hittable> object) { objects.push_back(object); }

  bool hit(const Ray &r, double r_tmin, double r_tmax, HitRecord &rec) const {
    HitRecord temp_rec;
    bool hit_anything = false;
    auto closest = r_tmax;

    for (const auto &obj : objects) {
      if (obj->hit(r, r_tmin, closest, temp_rec)) {
        hit_anything = true;
        closest = temp_rec.t;
        rec = temp_rec;
      }
    }

    return hit_anything;
  };
};

#endif // !HITTABLE_LIST_H
