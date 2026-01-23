#include <ryt/rtcore.hpp>
#include <cmath>

namespace RYT
{
    Sphere::Sphere(const Vec3& center, double radius, Material mat) : center(center), radius(std::fmax(0, radius)), mat(mat)
    {}

    bool Sphere::Hit(const Ray& r, Interval t, HitRecord& rec)
    {
	Vec3 CQ = center - r.Origin();
	auto a = r.Direction().LengthSquared();
	auto h = Dot(r.Direction(), CQ);
	auto c = CQ.LengthSquared() - radius * radius;

	auto discriminant = h*h - a*c;

	if(discriminant < 0) return false;

	auto sqrtd = std::sqrt(discriminant);

	// Get the nearest root that is in acceptable range
	auto root = (h - sqrtd) / a;

	if(!t.Surrounds(root))
	{
	    root = (h + sqrtd) / a;

	    if(!t.Surrounds(root)) return false;
	}

	// record hit then return true
	rec.t = root;
	rec.p = r.At(rec.t);

	Vec3 outward_normal = (rec.p - center) / radius;
	rec.SetFaceNormal(r, outward_normal);
	rec.mat = &mat;

	return true;
    }
}
