#ifndef RAY_H
#define RAY_H

#include <ryt/math/vec3.hpp>

namespace ryt
{
    class Ray
    {
	private:
		Vec3 orig;
		Vec3 dir;
	public:
	    
	    // constructors
	    Ray() {}
	    Ray(const Vec3& origin, const Vec3& direction) : orig(origin), dir(direction) {}
	    
	    // getters
	    const Vec3& origin() const
	    {
		return orig;
	    }

	    const Vec3& direction() const
	    {
		return dir;
	    }

	    Vec3 at(double t) const
	    {
		return orig + (t * dir);
	    }
    };
}
#endif
