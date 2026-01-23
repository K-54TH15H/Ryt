#include <ryt/rtcore.hpp>

namespace RYT
{
    double RandomDouble()
    {
	// returns radom in [0, 1)
	return std::rand() / (RAND_MAX + 1.0);
    }

    double RandomDouble(double min, double max)
    {
	// returns random in [min, max)
	return min + ((max - min) * RandomDouble());
    }
}
