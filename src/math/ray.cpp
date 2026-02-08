#include <ryt/math/ray.hpp>

namespace RYT {
// constructors
Ray::Ray() {}
Ray::Ray(const Vec3 &origin, const Vec3 &direction)
    : orig(origin), dir(direction) {}

Ray::Ray(const Vec3 &origin, const Vec3 &direction, double time)
    : orig(origin), dir(direction), time(time) {}

// getters
const Vec3 &Ray::Origin() const { return orig; }

const Vec3 &Ray::Direction() const { return dir; }

double Ray::Time() const { return time; }

Vec3 Ray::At(double t) const { return orig + (t * dir); }
} // namespace RYT
