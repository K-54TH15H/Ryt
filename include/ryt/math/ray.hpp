#ifndef RAY_HPP
#define RAY_HPP

#include <ryt/math/vec3.hpp>
namespace RYT {

// ********** RAY ********** //
class Ray {
private:
  Vec3 orig;
  Vec3 dir;
  double time;

public:
  // constructors
  Ray();
  Ray(const Vec3 &origin, const Vec3 &direction);
  Ray(const Vec3 &origin, const Vec3 &direction, double time);

  // getters
  const Vec3 &Origin() const;
  const Vec3 &Direction() const;
  double Time() const;
  Vec3 At(double t) const;
};
} // namespace RYT

#endif
