#include <ryt/math/interval.hpp>

namespace RYT {
// Default interval [inf, -inf] ( empty )
Interval::Interval() : min(+infinity), max(-infinity) {}

// Range based constructor
Interval::Interval(double min, double max) : min(min), max(max) {}

// Intervals based tight constructor
Interval::Interval(const Interval &a, const Interval &b) {
  min = (a.min <= b.min) ? a.min : b.min;
  max = (a.max >= b.max) ? a.max : b.max;
}

double Interval::Size() const { return max - min; }

bool Interval::Contains(double x) const { return min <= x && x <= max; }

bool Interval::Surrounds(double x) const { return min < x && x < max; }

double Interval::Clamp(double x) const {
  if (x < min)
    return min;
  else if (x > max)
    return max;
  else
    return x;
}

Interval Interval::Expand(double delta) const {
  double padd = delta / 2;
  return Interval(min - padd, max + padd);
}
} // namespace RYT
