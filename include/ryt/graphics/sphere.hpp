#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <ryt/core/aabb.hpp>
#include <ryt/core/hitrecord.hpp>
#include <ryt/graphics/material.hpp>
#include <ryt/math/ray.hpp>

namespace RYT {
// ********** SPHERE ********** //
class Sphere {
private:
  Ray center;
  double radius;
  Material mat;
  AABB bBox;

public:
  // Static Sphere Constructor
  Sphere(const Vec3 &staticCenter, double radius, Material mat);
  // Moving Sphere Constructor
  Sphere(const Vec3 &center1, const Vec3 &center2, double radius, Material mat);

  bool Hit(const Ray &r, Interval t, HitRecord &rec);

  // Retrieve Bounding Box
  AABB boundingBox() const;
};
} // namespace RYT

#endif
