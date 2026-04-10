#ifndef COMMON_HPP
#define COMMON_HPP

#include <device_types.h>
#include <limits>

namespace RYT {
// ********** Common ********** //
__host__ __device__ double MaxDouble(const double x, const double y);
__host__ __device__ double MinDouble(const double x, const double y);
__host__ __device__ void SwapDouble(double &x, double &y);
__host__ __device__ double RandomDouble();
__host__ __device__ double RandomDouble(double min, double max);
__host__ __device__ int RandomInt(int min, int max);

__host__ __device__ double DegreesToRadians(double degrees);

inline const double infinity = std::numeric_limits<double>::infinity();
inline const double pi = 3.1415926535897932385;
} // namespace RYT

#endif
