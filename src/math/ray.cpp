#include <ryt/rtcore.hpp>

namespace RYT
{
    // constructors
    Ray::Ray() {}
    Ray::Ray(const Vec3& origin, const Vec3& direction) : orig(origin), dir(direction) {}

    // getters
    const Vec3& Ray::Origin() const
    {
	return orig;
    }

    const Vec3& Ray::Direction() const
    {
	return dir;
    }

    Vec3 Ray::At(double t) const
    {
	return orig + (t * dir);
    }
}
