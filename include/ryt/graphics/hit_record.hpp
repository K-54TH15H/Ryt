#ifndef HIT_RECORD_H
#define HIT_RECORD_H

#include <ryt/math/vec3.hpp>
#include <ryt/math/ray.hpp>

namespace ryt
{
    class Material; // Forward Declaration

    class HitRecord
    {
	public:
	    Vec3 p;
	    Vec3 normal;
	    Material* mat; // This Doesn't Own the Material just points to it.
	    double t;
	    bool frontFace;

	    void SetFaceNormal(const Ray& r, const Vec3& outwardNormal)
	    {
		frontFace = Dot(r.Direction(), outwardNormal) < 0;

		normal = (frontFace) ? outwardNormal : -outwardNormal;
	    }
    };
}

#endif
