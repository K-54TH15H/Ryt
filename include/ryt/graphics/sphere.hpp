#ifndef SPHERE_H
#define SPHERE_H

#include "ryt/math/interval.hpp"
#include <ryt/math/ray.hpp>
#include <ryt/math/vec3.hpp>
#include <ryt/graphics/hit_record.hpp>

namespace ryt
{
    class Sphere
    {
	private:
	    vec3 center;
	    double radius;

	public:
	    Sphere(const vec3& center, double radius) : center(center), radius(std::fmax(0, radius))
	    {}

	    bool hit(const ray& r, Interval t, Hit_Record& rec)
	    {
		vec3 CQ = center - r.origin();
		auto a = r.direction().length_squared();
		auto h = dot(r.direction(), CQ);
		auto c = CQ.length_squared() - radius * radius;

		auto discriminant = h*h - a*c;

		if(discriminant < 0) return false;
		
		auto sqrtd = std::sqrt(discriminant);
		
		// Get the nearest root that is in acceptable range
		auto root = (h - sqrtd) / a;

		if(!t.surrounds(root))
		{
		    root = (h + sqrtd) / a;

		    if(!t.surrounds(root)) return false;
		}

		// record hit then return true
		rec.t = root;
		rec.p = r.at(rec.t);

		vec3 outward_normal = (rec.p - center) / radius;
		rec.set_face_normal(r, outward_normal);

		return true;
	    }

    };
}

#endif
