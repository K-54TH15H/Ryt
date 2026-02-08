#include <ryt/core/aabb.hpp>

namespace RYT {
// Default Box is NULL Box (Interval default is the empty constructor)
AABB::AABB() : x(Interval::empty), y(Interval::empty), z(Interval::empty) {}

AABB::AABB(const Interval &x, const Interval &y, const Interval &z)
    : x(x), y(y), z(z) {}

// Extremas of the box
AABB::AABB(const Vec3 &a, const Vec3 &b) {
  x = (a.x <= b.x) ? Interval(a.x, b.x) : Interval(b.x, a.x);
  y = (a.y <= b.y) ? Interval(a.y, b.y) : Interval(b.y, a.y);
  z = (a.z <= b.z) ? Interval(a.z, b.z) : Interval(b.z, a.z);
}

AABB::AABB(const AABB &boxA, const AABB &boxB) {
  x = Interval(boxA.x, boxB.x);
  y = Interval(boxA.y, boxB.y);
  z = Interval(boxA.z, boxB.z);
}

int AABB::LongestAxis() const {
  if (x.Size() > y.Size())
    return (x.Size() > z.Size()) ? 0 : 2;
  else
    return (y.Size() > z.Size()) ? 1 : 2;
}

const Interval &AABB::AxisInterval(int n) const {
  switch (n) {
  case 0:
    return x;
  case 1:
    return y;
  case 2:
    return z;
  default:
    return x;
  }
}

bool AABB::Hit(const Ray &r, Interval rayT) const {
  const Vec3 &rayOrig = r.Origin();
  const Vec3 &rayDir = r.Direction();

  double t0C;
  double t1C;
  double invC;

  // X-Axis
  invC = 1.0 / rayDir.x;
  t0C = (x.min - rayOrig.x) * invC;
  t1C = (x.max - rayOrig.x) * invC;
  if (invC < 0)
    std::swap(t0C, t1C);
  rayT.min = std::max(t0C, rayT.min);
  rayT.max = std::min(t1C, rayT.max);
  if (rayT.max <= rayT.min)
    return false;

  // Y-Axis
  invC = 1.0 / rayDir.y;
  t0C = (y.min - rayOrig.y) * invC;
  t1C = (y.max - rayOrig.y) * invC;
  if (invC < 0)
    std::swap(t0C, t1C);
  rayT.min = std::max(t0C, rayT.min);
  rayT.max = std::min(t1C, rayT.max);
  if (rayT.max <= rayT.min)
    return false;

  // Z-Axis
  invC = 1.0 / rayDir.z;
  t0C = (z.min - rayOrig.z) * invC;
  t1C = (z.max - rayOrig.z) * invC;
  if (invC < 0)
    std::swap(t0C, t1C);
  rayT.min = std::max(t0C, rayT.min);
  rayT.max = std::min(t1C, rayT.max);
  if (rayT.max <= rayT.min)
    return false;

  return true;
}
} // namespace RYT
