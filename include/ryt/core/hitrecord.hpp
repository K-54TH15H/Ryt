#ifndef HITREC_HPP
#define HITREC_HPP

#include <ryt/math/ray.hpp>

namespace RYT {
// ********** HitRecord ********** //
class Material; // Forward Declarations

class HitRecord {
public:
  Vec3 p;
  Vec3 normal;
  Material *mat; // This Doesn't Own the Material just points to it.
  double t;
  bool frontFace;

  void SetFaceNormal(const Ray &r, const Vec3 &outwardNormal);
};

} // namespace RYT
#endif
