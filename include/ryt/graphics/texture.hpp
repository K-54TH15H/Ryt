#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <ryt/graphics/color.hpp>
#include <ryt/utils/rytimage.hpp>

namespace RYT {
// Forward declarations
class RaytracingContext;
class Texture;

enum TextureType {
  NULLTEX,
  SOLID,
  CHECKER,
  IMAGE,
};

class SolidTexture {
public:
  SolidTexture(const Color &albedo);
  SolidTexture(double r, double g, double b);

  Color Value(double u, double v, const Vec3 &p) const;

private:
  Color albedo;
};

class CheckerTexture {
private:
  double invScale;
  int evenId;
  int oddId;

public:
  CheckerTexture(double scale, int evenId, int oddId);
  // CheckerTexture(double scale, const Color& c1, const Color& c2);

  Color Value(double u, double v, const Vec3 &p,
              const RaytracingContext *context) const;
};

class ImageTexture
{
    public:
	ImageTexture(int imaegId);

	Color Value(double u, double v, const Vec3& p, const RaytracingContext* context) const;
    
    private:
	int imageId;		    
};

class Texture {
public:
  // Constructors
  Texture();
  Texture(const SolidTexture solidTexture);
  Texture(const CheckerTexture checkerTexture);
  Texture(const ImageTexture imageTexture);
  Texture(const Color color);

  Color Value(double u, double v, const Vec3 &p,
              const RaytracingContext *context) const;

private:
  TextureType type;
  union MemberData {
    SolidTexture solidTexture;
    CheckerTexture checkerTexture;
    ImageTexture imageTexture;

    MemberData() {}
    ~MemberData() {}
  } data;
};
} // namespace RYT
#endif
