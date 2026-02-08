#include <cstdlib>
#include <ryt/math/common.hpp>

namespace RYT {
double RandomDouble() {
  // returns radom in [0, 1)
  return std::rand() / (RAND_MAX + 1.0);
}

double RandomDouble(double min, double max) {
  // returns random in [min, max)
  return min + ((max - min) * RandomDouble());
}

int RandomInt(int min, int max) { return int(RandomDouble(min, max + 1)); }
double DegreesToRadians(double degrees) { return degrees * pi / 180.0; }
} // namespace RYT
