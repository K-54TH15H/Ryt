#ifndef COMMON_HPP
#define COMMON_HPP

#include <curand_kernel.h>
#include <device_types.h>

#define RYT_PI 3.1415926535897932385
#define RYT_INFINITY 1e30

namespace RYT {
// ********** Common ********** //
__host__ __device__ double MaxDouble(const double x, const double y);
__host__ __device__ double MinDouble(const double x, const double y);
__host__ __device__ void SwapDouble(double &x, double &y);

__host__ __device__ double RandomDouble(curandState *state = nullptr);

__host__ __device__ double RandomDouble(double min, double max,
                                        curandState *state = nullptr);
__host__ __device__ int RandomInt(int min, int max,
                                  curandState *state = nullptr);

__host__ __device__ double DegreesToRadians(double degrees);

} // namespace RYT

#endif
