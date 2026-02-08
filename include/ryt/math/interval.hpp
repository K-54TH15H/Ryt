#ifndef INTERVAL_HPP
#define INTERVAL_HPP

#include <ryt/math/common.hpp>

namespace RYT {
// ********** Interval ********** //

class Interval {
public:
  double min, max;

  // Default interval [inf, -inf] ( empty )
  Interval();
  // Range based constructor
  Interval(double min, double max);
  // Intervals based tight constructor
  Interval(const Interval &a, const Interval &b);

  double Size() const;
  bool Contains(double x) const;
  bool Surrounds(double x) const;

  double Clamp(double x) const;
  Interval Expand(double delta) const;

  static const Interval empty, universe;
};

// Static Constant Intervals
inline const Interval Interval::empty = Interval(+infinity, -infinity);
inline const Interval Interval::universe = Interval(-infinity, +infinity);
} // namespace RYT
#endif
