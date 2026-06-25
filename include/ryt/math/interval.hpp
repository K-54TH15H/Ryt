#ifndef INTERVAL_HPP
#define INTERVAL_HPP
#include <device_types.h>
#include <ryt/math/common.hpp>

namespace RYT {
// ********** Interval ********** //

class Interval {
public:
  double min, max;

  // Default interval [inf, -inf] ( empty )
  __host__ __device__ Interval();
  // Range based constructor
  __host__ __device__ Interval(double min, double max);
  // Intervals based tight constructor
  __host__ __device__ Interval(const Interval &a, const Interval &b);

  __host__ __device__ double Size() const;
  __host__ __device__ bool Contains(double x) const;
  __host__ __device__ bool Surrounds(double x) const;

  __host__ __device__ double Clamp(double x) const;
  __host__ __device__ Interval Expand(double delta) const;

  static const Interval empty, universe;
};

// Static Constant Intervals
inline const Interval Interval::empty = Interval(+RYT_INFINITY, -RYT_INFINITY);
inline const Interval Interval::universe =
    Interval(-RYT_INFINITY, +RYT_INFINITY);
} // namespace RYT
#endif
