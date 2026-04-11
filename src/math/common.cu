#include <cuda_runtime.h>
#include <curand_kernel.h>
#include <random>
#include <ryt/math/common.hpp>

namespace RYT {
__host__ __device__ double MaxDouble(const double x, const double y) {
  if (x > y)
    return x;
  return y;
}

__host__ __device__ double MinDouble(const double x, const double y) {
  if (x < y)
    return x;
  return y;
}

__host__ __device__ void SwapDouble(double &x, double &y) {
  double z = x;
  x = y;
  y = z;
}

__host__ __device__ double RandomDouble() {
#if (defined(__CUDA_ARCH__) && (__CUDA_ARCH__ > 0))
  return 0.5;
#else
  static thread_local std::mt19937 generator;
  std::uniform_real_distribution<double> distribution(0, 1);
  return distribution(generator);
#endif
}

__host__ __device__ double RandomDouble(double min, double max) {
  // returns random in [min, max)
  return min + ((max - min) * RandomDouble());
}

__host__ __device__ int RandomInt(int min, int max) {
  return int(RandomDouble(min, max + 1));
}
__host__ __device__ double DegreesToRadians(double degrees) {
  return degrees * RYT_PI / 180.0;
}
} // namespace RYT
