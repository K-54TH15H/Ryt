#include <ryt/graphics/texture.hpp>

namespace RYT
{
    SolidTexture::SolidTexture(const Color& albedo) : albedo(albedo) {}
    SolidTexture::SolidTexture(double r, double g, double b) : SolidTexture(Color(r, g, b)) {}
    Color SolidTexture::Value(double u, double v, const Vec3& p) const { return albedo; }
    
    CheckerTexture::CheckerTexture(double scale, Texture* even, Texture* odd) : invScale(1.0 / scale), even(even), odd(odd) {}
    // CheckerTexture::CheckerTexture(double scale, const Color& c1, const Color& c2) : invScale(1.0 / scale), even(Texture(c1)), odd(Texture(c2)) {}
    Color CheckerTexture::Value(double u, double v, const Vec3& p) const 
    {
	int xPos = (invScale * p.x) / 1;
	int yPos = (invScale * p.y) / 1;
	int zPos = (invScale * p.z) / 1;

	bool isEven = (xPos + yPos + zPos) % 2 == 0;

	return isEven ? even->Value(u, v, p) : odd->Value(u, v, p);
    }

    Texture::Texture(const SolidTexture solidTexture) : type(SOLID) { data.solidTexture = solidTexture; } 
    Texture::Texture(const CheckerTexture checkerTexture) : type(CHECKER) { data.checkerTexture = checkerTexture; }
    Texture::Texture(const Color color) : type(SOLID) { data.solidTexture = SolidTexture(color); }

    Color Texture::Value(double u, double v, const Vec3& p) const
    {
	switch(type)
	{
	    case SOLID:
		return data.solidTexture.Value(u, v, p);
	    
	    case CHECKER:
		return data.checkerTexture.Value(u, v, p);

	    default:
		return {0, 0, 0};
	}
    }
}
