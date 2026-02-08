#include <ryt/core/hittable.hpp>

namespace RYT {
Hittable::Hittable() { type = NONE; }

Hittable::Hittable(Sphere s) {
  type = SPHERE;
  data.sphere = s;
  bBox = s.boundingBox();
}

Hittable::~Hittable() {
  switch (type) {
  case SPHERE:
    ((data.sphere)).~Sphere(); // Calling Destructor Call Explicitly
    break;

  default: // None
    break;
  }
}

bool Hittable::Hit(const Ray &r, Interval t, HitRecord &rec) {

  switch (type) {
  case SPHERE:
    return ((data.sphere)).Hit(r, t, rec);

  // Hit None
  default:
    return false;
  }
}

} // namespace RYT
