#include <ryt/math/ray.hpp>

namespace RYT {
// constructors
__host__ __device__ Ray::Ray() {}
__host__ __device__ Ray::Ray(const Vec3 &origin, const Vec3 &direction)
    : orig(origin), dir(direction) {}

__host__ __device__ Ray::Ray(const Vec3 &origin, const Vec3 &direction,
                             double time)
    : orig(origin), dir(direction), time(time) {}

// getters
__host__ __device__ const Vec3 &Ray::Origin() const { return orig; }

__host__ __device__ const Vec3 &Ray::Direction() const { return dir; }

__host__ __device__ double Ray::Time() const { return time; }

__host__ __device__ Vec3 Ray::At(double t) const { return orig + (t * dir); }
} // namespace RYT
