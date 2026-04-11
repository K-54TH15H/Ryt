#include <ryt/math/interval.hpp>

namespace RYT {
// Default interval [inf, -inf] ( empty )
__host__ __device__ Interval::Interval()
    : min(+RYT_INFINITY), max(-RYT_INFINITY) {}

// Range based constructor
__host__ __device__ Interval::Interval(double min, double max)
    : min(min), max(max) {}

// Intervals based tight constructor
__host__ __device__ Interval::Interval(const Interval &a, const Interval &b) {
  min = (a.min <= b.min) ? a.min : b.min;
  max = (a.max >= b.max) ? a.max : b.max;
}

__host__ __device__ double Interval::Size() const { return max - min; }

__host__ __device__ bool Interval::Contains(double x) const {
  return min <= x && x <= max;
}

__host__ __device__ bool Interval::Surrounds(double x) const {
  return min < x && x < max;
}

__host__ __device__ double Interval::Clamp(double x) const {
  if (x < min)
    return min;
  else if (x > max)
    return max;
  else
    return x;
}

__host__ __device__ Interval Interval::Expand(double delta) const {
  double padd = delta / 2;
  return Interval(min - padd, max + padd);
}
} // namespace RYT
