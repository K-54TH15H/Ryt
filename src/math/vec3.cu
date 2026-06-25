#include <cmath>

#include <ryt/math/common.hpp>
#include <ryt/math/vec3.hpp>

namespace RYT {
// ********** MEMBER FUNCTIONS ********** //

// constructors
__host__ __device__ Vec3::Vec3() : x(0), y(0), z(0) {}
__host__ __device__ Vec3::Vec3(double x, double y, double z)
    : x(x), y(y), z(z) {}

// operator overloadings
__host__ __device__ Vec3 Vec3::operator-() const { return Vec3(-x, -y, -z); }

__host__ __device__ Vec3 &Vec3::operator+=(const Vec3 &v) {
  x += v.x;
  y += v.y;
  z += v.z;

  return *this;
}

__host__ __device__ Vec3 &Vec3::operator*=(double t) {
  x *= t;
  y *= t;
  z *= t;

  return *this;
}

__host__ __device__ Vec3 &Vec3::operator/=(double t) { return *this *= 1 / t; }

// Length functions
__host__ __device__ double Vec3::LengthSquared() const {
  return ((x * x) + (y * y) + (z * z));
}

__host__ __device__ double Vec3::Length() const {
  return std::sqrt(LengthSquared());
}

__host__ __device__ bool Vec3::NearZero() const {
  auto co = 1e-8; // cuttoff
  return (std::fabs(x) < co) && (std::fabs(y) < co) && (std::fabs(z) < co);
}

__host__ __device__ Vec3 Vec3::Random(curandState *state) {
  return Vec3(RandomDouble(state), RandomDouble(state), RandomDouble(state));
}

__host__ __device__ Vec3 Vec3::Random(double min, double max,
                                      curandState *state) {
  return Vec3(RandomDouble(min, max, state), RandomDouble(min, max, state),
              RandomDouble(min, max, state));
}

__host__ std::ostream &operator<<(std::ostream &os, const Vec3 &v) {
  return os << v.x << ' ' << v.y << ' ' << v.z;
}

__host__ __device__ Vec3 operator+(const Vec3 &u, const Vec3 &v) {
  return Vec3((u.x + v.x), (u.y + v.y), (u.z + v.z));
}

__host__ __device__ Vec3 operator-(const Vec3 &u, const Vec3 &v) {
  return Vec3((u.x - v.x), (u.y - v.y), (u.z - v.z));
}

__host__ __device__ Vec3 operator*(double t, const Vec3 &v) {
  return Vec3(t * v.x, t * v.y, t * v.z);
}

__host__ __device__ Vec3 operator*(const Vec3 &u, const Vec3 &v) {
  return Vec3(u.x * v.x, u.y * v.y, u.z * v.z);
}

__host__ __device__ Vec3 operator/(const Vec3 &v, double t) {
  return (1 / t) * v;
}

__host__ __device__ double Dot(const Vec3 &u, const Vec3 &v) {
  return (u.x * v.x) + (u.y * v.y) + (u.z * v.z);
}

__host__ __device__ Vec3 Cross(const Vec3 &u, const Vec3 &v) {
  return Vec3(u.y * v.z - u.z * v.y, u.z * v.x - u.x * v.z,
              u.x * v.y - u.y * v.x);
}

__host__ __device__ Vec3 UnitVector(const Vec3 &v) { return v / v.Length(); }

__host__ __device__ Vec3 RandomUnitVector(curandState *state) {
  while (true) {
    Vec3 p = Vec3::Random(-1, 1, state);
    double lenSq = p.LengthSquared();

    if (1e-160 < lenSq && lenSq <= 1)
      return (p / sqrt(lenSq));
  }
}

__host__ __device__ Vec3 RandomOnHemisphere(const Vec3 &normal,
                                            curandState *state) {
  Vec3 onUnitSphere = RandomUnitVector(state);

  if (Dot(onUnitSphere, normal) > 0.0)
    return onUnitSphere;
  else
    return -onUnitSphere;
}

__host__ __device__ Vec3 RandomInUnitDisk(curandState *state) {
  return Vec3(RandomDouble(-0.7, 0.7, state), RandomDouble(-0.7, 0.7, state),
              0);
}

__host__ __device__ Vec3 Reflect(const Vec3 &v, const Vec3 &n) {
  return v - (2 * Dot(v, n) * n);
}

__host__ __device__ Vec3 Refract(const Vec3 &uv, const Vec3 &n,
                                 double etaiOverEtat) {
  double cosTheta = std::fmin(Dot(-uv, n), 1.0);
  Vec3 rOutPerp = etaiOverEtat * (uv + cosTheta * n);
  Vec3 rOutParallel = -std::sqrt(std::fabs(1.0 - rOutPerp.LengthSquared())) * n;

  return rOutPerp + rOutParallel;
}
} // namespace RYT
