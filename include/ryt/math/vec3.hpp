#ifndef VEC3_HPP
#define VEC3_HPP

#include <iostream>

namespace RYT {
// ********** VEC3 ********** //
class Vec3 {
public:
  // data
  double x, y, z;

  // constructors
  Vec3();
  Vec3(double x, double y, double z);

  // operator overloadings
  Vec3 operator-() const;

  Vec3 &operator+=(const Vec3 &v);
  Vec3 &operator*=(double t);
  Vec3 &operator/=(double t);

  // length functions
  double LengthSquared() const;
  double Length() const;

  bool NearZero() const;

  static Vec3 Random();

  static Vec3 Random(double min, double max);
};

// vector utility functions
std::ostream &operator<<(std::ostream &os, const Vec3 &v);
Vec3 operator+(const Vec3 &u, const Vec3 &v);
Vec3 operator-(const Vec3 &u, const Vec3 &v);
Vec3 operator*(double t, const Vec3 &v);
Vec3 operator*(const Vec3 &u, const Vec3 &v);
Vec3 operator/(const Vec3 &v, double t);
double Dot(const Vec3 &u, const Vec3 &v);
Vec3 Cross(const Vec3 &u, const Vec3 &v);
Vec3 UnitVector(const Vec3 &v);
Vec3 RandomUnitVector();
Vec3 RandomOnHemisphere(const Vec3 &normal);
Vec3 RandomInUnitDisk();
Vec3 Reflect(const Vec3 &v, const Vec3 &n);
Vec3 Refract(const Vec3 &uv, const Vec3 &n, double etai_over_etat);

} // namespace RYT
#endif
