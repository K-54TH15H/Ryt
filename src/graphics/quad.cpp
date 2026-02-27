#include <ryt/core/hitrecord.hpp>
#include <ryt/math/vec3.hpp>
#include <ryt/graphics/quad.hpp>
#include <cmath>

namespace RYT
{
    Quad::Quad(const Vec3& q, const Vec3& u, const Vec3& v, Material mat) 
	: Q(q), u(u), v(v), mat(mat)
    {
	Vec3 n = Cross(u, v);
	normal = UnitVector(n);
	D = Dot(normal, Q);
	w = n / Dot(n, n);

	SetBoundingBox();
    }

    void Quad::SetBoundingBox()
    {
	AABB bBoxDiagonalA = AABB(Q, Q + u + v);
	AABB bBoxDiagonalB = AABB(Q + u, Q + v);

	bBox = AABB(bBoxDiagonalA, bBoxDiagonalB);
    }

    AABB Quad::BoundingBox() const { return bBox; }

    bool Quad::Hit(const Ray& r, Interval rayT, HitRecord& rec)
    {
	double denominator = Dot(normal, r.Direction());

	// No hit - if parallel
	if(std::fabs(denominator) < 1e-8) return false;

	// Return false if the hit point parameter t is outside the ray interval.
	double t = (D - Dot(normal, r.Origin())) / denominator;

	if(!rayT.Contains(t)) return false;

	// Check whether it hits the quad
	Vec3 intersection = r.At(t);
	Vec3 planarHitPt = intersection - Q;
	double alpha = Dot(w, Cross(planarHitPt, v));
	double beta = Dot(w, Cross(u, planarHitPt));

	if(!(IsInterior(alpha, beta, rec))) return false;

	rec.t = t;
	rec.p = intersection;
	rec.mat = &mat;
	rec.SetFaceNormal(r, normal);
	
	return true;
    }

    bool Quad::IsInterior(double alpha, double beta, HitRecord& rec) const
    {
	Interval UnitInerval = Interval(0, 1);

	if(!UnitInerval.Contains(alpha) || !UnitInerval.Contains(beta)) return false;

	rec.u = alpha;
	rec.v = beta;

	return true;
    }
}
