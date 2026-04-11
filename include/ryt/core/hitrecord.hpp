#ifndef HITREC_HPP
#define HITREC_HPP

#include <ryt/math/ray.hpp>

namespace RYT {
// ********** HitRecord ********** //
class RaytracingContext; // Forward Declarations

class HitRecord {
public:
  bool hit = false;

  Vec3 p;
  Vec3 normal;
  int materialId;
  double t;
  bool frontFace;

  // Store the context in which the hit was recorded
  const RaytracingContext *context;

  // Surface co-ordinates of the ray-object intersection
  double u;
  double v;

  __host__ __device__ void SetFaceNormal(const Ray &r,
                                         const Vec3 &outwardNormal);
};

} // namespace RYT
#endif
