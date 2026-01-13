#ifndef RAY_H
#define RAY_H

#include <ryt/math/vec3.hpp>

namespace ryt
{
    class ray
    {
	private:
		vec3 orig;
		vec3 dir;
	public:
	    
	    // constructors
	    ray() {}
	    ray(const vec3& origin, const vec3& direction) : orig(origin), dir(direction) {}
	    
	    // getters
	    const vec3& origin() const
	    {
		return orig;
	    }

	    const vec3& direction() const
	    {
		return dir;
	    }

	    vec3 at(double t) const
	    {
		return orig + (t * dir);
	    }
    };
}
#endif
