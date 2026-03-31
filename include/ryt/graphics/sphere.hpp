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
  int materialId;
  AABB bBox;

public:
  // Static Sphere Constructor
  Sphere(const Vec3 &staticCenter, double radius, int materialId);
  // Moving Sphere Constructor
  Sphere(const Vec3 &center1, const Vec3 &center2, double radius, int materialId);

  bool Hit(const Ray &r, Interval t, HitRecord &rec);

  // Retrieve Bounding Box
  AABB boundingBox() const;

  void GetSphereUV(const Vec3 &p, HitRecord &hitrecord);
};
} // namespace RYT

#endif
