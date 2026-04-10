#include <ryt/core/hitrecord.hpp>

namespace RYT {
__host__ __device__ void HitRecord::SetFaceNormal(const Ray &r,
                                                  const Vec3 &outwardNormal) {
  frontFace = Dot(r.Direction(), outwardNormal) < 0;

  normal = (frontFace) ? outwardNormal : -outwardNormal;
}
} // namespace RYT
