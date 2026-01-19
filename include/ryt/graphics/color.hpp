#ifndef COLOR_H
#define COLOR_H

#include <cmath>
#include <ryt/math/vec3.hpp>
#include <ryt/math/interval.hpp>

#include <iostream>


namespace ryt
{
    using Color = Vec3; // alias for rt::Vec3 as color as an context - might need to modify

    inline void LinearToGamma(double& linearComponent)
    {
	linearComponent = (linearComponent > 0) ? std::sqrt(linearComponent) : 0;
    }

    inline void WriteColor(std::ostream& os, const Color& pixelColor)
    {
	auto r = pixelColor.x;
	auto g = pixelColor.y;
	auto b = pixelColor.z;
	
	// Gamma correction
	LinearToGamma(r);
	LinearToGamma(g);
	LinearToGamma(b);

	static const Interval intensity(0.000, 0.999);

	int rb = int(256 * intensity.Clamp(r));
	int gb = int(256 * intensity.Clamp(g));
	int bb = int(256 * intensity.Clamp(b));

	os << rb << ' ' << gb << ' ' << bb << std::endl;
    }
}

#endif
