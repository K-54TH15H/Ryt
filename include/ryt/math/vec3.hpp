#ifndef VEC3_HPP
#define VEC3_HPP
#include <curand_kernel.h>
#include <device_types.h>
#include <iostream>

namespace RYT {
// ********** VEC3 ********** //
class Vec3 {
public:
  // data
  double x, y, z;

  // constructors
  __host__ __device__ Vec3();
  __host__ __device__ Vec3(double x, double y, double z);

  // operator overloadings
  __host__ __device__ Vec3 operator-() const;

  __host__ __device__ Vec3 &operator+=(const Vec3 &v);
  __host__ __device__ Vec3 &operator*=(double t);
  __host__ __device__ Vec3 &operator/=(double t);

  // length functions
  __host__ __device__ double LengthSquared() const;
  __host__ __device__ double Length() const;

  __host__ __device__ bool NearZero() const;

  __host__ __device__ static Vec3 Random(curandState *state = nullptr);

  __host__ __device__ static Vec3 Random(double min, double max,
                                         curandState *state = nullptr);
};

// vector utility functions
__host__ std::ostream &operator<<(std::ostream &os, const Vec3 &v);
__host__ __device__ Vec3 operator+(const Vec3 &u, const Vec3 &v);
__host__ __device__ Vec3 operator-(const Vec3 &u, const Vec3 &v);
__host__ __device__ Vec3 operator*(double t, const Vec3 &v);
__host__ __device__ Vec3 operator*(const Vec3 &u, const Vec3 &v);
__host__ __device__ Vec3 operator/(const Vec3 &v, double t);
__host__ __device__ double Dot(const Vec3 &u, const Vec3 &v);
__host__ __device__ Vec3 Cross(const Vec3 &u, const Vec3 &v);
__host__ __device__ Vec3 UnitVector(const Vec3 &v);
__host__ __device__ Vec3 RandomUnitVector(curandState *state = nullptr);
__host__ __device__ Vec3 RandomOnHemisphere(const Vec3 &normal,
                                            curandState *state = nullptr);
__host__ __device__ Vec3 RandomInUnitDisk(curandState *state = nullptr);
__host__ __device__ Vec3 Reflect(const Vec3 &v, const Vec3 &n);
__host__ __device__ Vec3 Refract(const Vec3 &uv, const Vec3 &n,
                                 double etai_over_etat);

} // namespace RYT
#endif
