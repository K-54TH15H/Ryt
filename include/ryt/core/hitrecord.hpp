#ifndef HITREC_HPP
#define HITREC_HPP

#include <ryt/math/ray.hpp>

namespace RYT {
// ********** HitRecord ********** //
class Material;          // Forward Declarations
class RaytracingContext; // Forward Declarations

class HitRecord {
public:
  Vec3 p;
  Vec3 normal;
  Material *mat; // This Doesn't Own the Material just points to it.
  double t;
  bool frontFace;

  // Store the context in which the hit was recorded
  const RaytracingContext *context;

  // Surface co-ordinates of the ray-object intersection
  double u;
  double v;

  void SetFaceNormal(const Ray &r, const Vec3 &outwardNormal);
};

} // namespace RYT
#endif
