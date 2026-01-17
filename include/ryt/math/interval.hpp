#ifndef INTERVAL_H
#define INTERVAL_H

#include <limits>

namespace ryt
{
    // Interval constants
    inline const double infinity = std::numeric_limits<double>::infinity();
    inline const double pi = 3.1415926535897932385;

    class Interval
    {
	public:
	    double min, max;
	    
	    // Default interval [inf, -inf] ( empty )
	    Interval() : min(+infinity), max(-infinity) {}
	    
	    // Range based constructor
	    Interval(double min, double max) : min(min), max(max) {}

	    double size() const
	    {
		return max - min;
	    }

	    bool contains(double x) const
	    {
		return min <= x && x <= max;
	    }

	    bool surrounds(double x) const
	    {
		return min < x && x < max;
	    }

	    static const Interval empty, universe;
    };

    // Static Constant Intervals
    inline const Interval Interval::empty = Interval(+infinity, -infinity);
    inline const Interval Interval::universe = Interval(-infinity, +infinity);
}
#endif
