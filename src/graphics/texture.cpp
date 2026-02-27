#include <ryt/core/rtcontext.hpp>
#include <ryt/graphics/texture.hpp>

namespace RYT {
SolidTexture::SolidTexture(const Color &albedo) : albedo(albedo) {}
SolidTexture::SolidTexture(double r, double g, double b)
    : SolidTexture(Color(r, g, b)) {}
Color SolidTexture::Value(double u, double v, const Vec3 &p) const {
  return albedo;
}

CheckerTexture::CheckerTexture(double scale, int evenId, int oddId)
    : invScale(1.0 / scale), evenId(evenId), oddId(oddId) {}
// CheckerTexture::CheckerTexture(double scale, const Color& c1, const Color&
// c2) : invScale(1.0 / scale), even(Texture(c1)), odd(Texture(c2)) {}
Color CheckerTexture::Value(double u, double v, const Vec3 &p,
                            const RaytracingContext *context) const {
  int xPos = (invScale * p.x) / 1;
  int yPos = (invScale * p.y) / 1;
  int zPos = (invScale * p.z) / 1;

  bool isEven = (xPos + yPos + zPos) % 2 == 0;
  int targetId = isEven ? evenId : oddId;

  return context->textures[targetId].Value(u, v, p, context);
}

ImageTexture::ImageTexture(const char* fileName) : image(fileName) {}

Color ImageTexture::Value(double u, double v, const Vec3& p) const
{
    // No Image hence cyan color [debug]
    if(image.Height() <= 0) return Color(0, 1, 1); 

    u = Interval(0, 1).Clamp(u);
    v = 1.0 - Interval(0, 1).Clamp(v);

    int i = int(u * image.Width());
    int j = int(v * image.Height());
    const unsigned char* pixel = image.PixelData(i, j);

    double colorScale = 1.0 / 255.0;
    return Color(colorScale * pixel[0], colorScale * pixel[1], colorScale * pixel[2]);
}

Texture::Texture() : type(NULLTEX) {}
Texture::Texture(const SolidTexture solidTexture) : type(SOLID) {
  data.solidTexture = solidTexture;
}
Texture::Texture(const CheckerTexture checkerTexture) : type(CHECKER) {
  data.checkerTexture = checkerTexture;
}
Texture::Texture(const Color color) : type(SOLID) {
  data.solidTexture = SolidTexture(color);
}

Texture::Texture(const ImageTexture imageTexture) : type(IMAGE) {
    data.imageTexture = imageTexture;
}

Color Texture::Value(double u, double v, const Vec3 &p,
                     const RaytracingContext *context) const {
  switch (type) {
  case SOLID:
    return data.solidTexture.Value(u, v, p);

  case CHECKER:
    return data.checkerTexture.Value(u, v, p, context);

  case IMAGE:
    return data.imageTexture.Value(u, v, p);

  default:
    return {0, 0, 0};
  }
}

} // namespace RYT
