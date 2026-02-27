#ifndef QUAD_HPP
#define QUAD_HPP

#include <ryt/core/hitrecord.hpp>
#include <ryt/core/aabb.hpp>
#include <ryt/graphics/material.hpp>

namespace RYT
{
    class Quad
    {
	public:
	    Quad(const Vec3& q, const Vec3& u, const Vec3& v, Material mat);
	    void SetBoundingBox();
	    AABB BoundingBox() const;
	    bool Hit(const Ray&r, Interval rayT, HitRecord& rec);

	private:
	    Vec3 Q;
	    Vec3 u;
	    Vec3 v;
	    Vec3 normal;
	    Vec3 w;

	    double D;
	    Material mat;
	    AABB bBox;

	    bool IsInterior(double alpha, double beta, HitRecord& rec) const;
    };
}
#endif
