#ifndef COMMON_HPP
#define COMMON_HPP

#include <limits>
namespace RYT {
// ********** Common ********** //
double RandomDouble();
double RandomDouble(double min, double max);
int RandomInt(int min, int max);

double DegreesToRadians(double degrees);

inline const double infinity = std::numeric_limits<double>::infinity();
inline const double pi = 3.1415926535897932385;
} // namespace RYT

#endif
