#ifndef AABB_HPP
#define AABB_HPP

#include <ryt/math/interval.hpp>
#include <ryt/math/ray.hpp>

namespace RYT {

// ********** AABB ********** //
class AABB {
public:
  Interval x, y, z;
  // constructors
  AABB();
  AABB(const Interval &x, const Interval &y, const Interval &z);
  AABB(const Vec3 &a, const Vec3 &b);
  AABB(const AABB &boxA, const AABB &boxB);

  int LongestAxis() const;
  const Interval &AxisInterval(int n) const;
  bool Hit(const Ray &r, Interval rayT) const;
};
} // namespace RYT
#endif
