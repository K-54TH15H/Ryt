#include <cmath>
#include <ryt/rtcore.hpp>

namespace RYT {

Sphere::Sphere(const Vec3 &staticCenter, double radius, Material mat)
    : center(staticCenter, Vec3(0, 0, 0)), radius(std::fmax(0, radius)),
      mat(mat) {}

Sphere::Sphere(const Vec3 &center1, const Vec3 &center2, double radius,
               Material mat)
    : center(center1, center2 - center1), radius(std::fmax(0, radius)),
      mat(mat) {}

bool Sphere::Hit(const Ray &r, Interval t, HitRecord &rec) {
  Vec3 currentCenter = center.At(r.Time());

  Vec3 CQ = currentCenter - r.Origin();
  auto a = r.Direction().LengthSquared();
  auto h = Dot(r.Direction(), CQ);
  auto c = CQ.LengthSquared() - radius * radius;

  auto discriminant = h * h - a * c;

  if (discriminant < 0)
    return false;

  auto sqrtd = std::sqrt(discriminant);

  // Get the nearest root that is in acceptable range
  auto root = (h - sqrtd) / a;

  if (!t.Surrounds(root)) {
    root = (h + sqrtd) / a;

    if (!t.Surrounds(root))
      return false;
  }

  // record hit then return true
  rec.t = root;
  rec.p = r.At(rec.t);

  Vec3 outward_normal = (rec.p - currentCenter) / radius;
  rec.SetFaceNormal(r, outward_normal);
  rec.mat = &mat;

  return true;
}
} // namespace RYT
