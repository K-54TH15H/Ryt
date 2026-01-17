#ifndef COLOR_H
#define COLOR_H

#include <ryt/math/vec3.hpp>
#include <iostream>


namespace ryt
{
    using color = vec3; // alias for rt::vec3 as color as an context - might need to modify
    
    inline void write_color(std::ostream& os, const color& pixel_color)
    {
	auto r = pixel_color.x;
	auto g = pixel_color.y;
	auto b = pixel_color.z;

	int rb = int(255.999 * r);
	int gb = int(255.999 * g);
	int bb = int(255.999 * b);

	os << rb << ' ' << gb << ' ' << bb << std::endl;
    }
}

#endif
