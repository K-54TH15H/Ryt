#ifndef HITTABLE_HPP
#define HITTABLE_HPP

#include <ryt/core/aabb.hpp>
#include <ryt/graphics/quad.hpp>
#include <ryt/graphics/sphere.hpp>

namespace RYT {
// *********** HITTABLE ********** //
// Tag for Geometry type
enum GeometryType { SPHERE, QUAD, NONE };

class Hittable {
public:
  GeometryType type;
  AABB bBox;

  union MemberData {
    Sphere sphere;
    Quad quad;
    // default constructors get destroyed placeholder constructors and
    // destrcutors manually handled via class constructors and destrcutors
    MemberData() {}
    ~MemberData() {}

  } data;

  Hittable();
  Hittable(Sphere s);
  Hittable(Quad q);

  ~Hittable();

  bool Hit(const Ray &r, Interval t, HitRecord &rec);
};
} // namespace RYT
#endif
