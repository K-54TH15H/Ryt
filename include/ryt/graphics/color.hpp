#ifndef COLOR_HPP
#define COLOR_HPP

#include <iostream>
#include <ryt/math/vec3.hpp>

namespace RYT {
// ********** Color ********** //
using Color =
    Vec3; // alias for rt::Vec3 as color as an context - might need to modify

void LinearToGamma(double &linearComponent);
void WriteColor(std::ostream &os, const Color &pixelColor);
} // namespace RYT
#endif
