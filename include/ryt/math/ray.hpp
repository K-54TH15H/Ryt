#ifndef RAY_HPP
#define RAY_HPP

#include <ryt/math/vec3.hpp>
namespace RYT {

// ********** RAY ********** //
class Ray {
private:
  Vec3 orig;
  Vec3 dir;
  double time;

public:
  // constructors
  __host__ __device__ Ray();
  __host__ __device__ Ray(const Vec3 &origin, const Vec3 &direction);
  __host__ __device__ Ray(const Vec3 &origin, const Vec3 &direction,
                          double time);

  // getters
  __host__ __device__ const Vec3 &Origin() const;
  __host__ __device__ const Vec3 &Direction() const;
  __host__ __device__ double Time() const;
  __host__ __device__ Vec3 At(double t) const;
};
} // namespace RYT

#endif
