#ifndef HIT_RECORD_H
#define HIT_RECORD_H

#include <ryt/math/vec3.hpp>
#include <ryt/math/ray.hpp>

namespace ryt
{
    class Material; // Forward Declaration

    class Hit_Record
    {
	public:
	    vec3 p;
	    vec3 normal;
	    Material* mat; // This Doesn't Own the Material just points to it.
	    double t;
	    bool front_face;

	    void set_face_normal(const ray& r, const vec3& outward_normal)
	    {
		front_face = dot(r.direction(), outward_normal) < 0;

		normal = (front_face) ? outward_normal : -outward_normal;
	    }
    };
}

#endif
