#include <cmath>
#include <ryt/graphics/color.hpp>
#include <ryt/math/interval.hpp>

namespace RYT {
void LinearToGamma(double &linearComponent) {
  linearComponent = (linearComponent > 0) ? std::sqrt(linearComponent) : 0;
}

void WriteColor(std::ostream &os, const Color &pixelColor) {
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
} // namespace RYT
