#include <ryt/graphics/texture.hpp>

namespace RYT
{
    SolidColor::SolidColor(const Color& albedo) : albedo(albedo) {}
    SolidColor::SolidColor(double r, double g, double b) : SolidColor(Color(r, g, b)) {}
    Color SolidColor::Value(double u, double v, const Vec3& p) const { return albedo; }
    
    CheckerTexture::CheckerTexture(double scale, Texture* even, Texture* odd) : invScale(1.0 / scale), even(even), odd(odd) {}
    
    Color CheckerTexture::Value(double u, double v, const Vec3& p) const 
    {
	int xPos = (invScale * p.x) / 1;
	int yPos = (invScale * p.y) / 1;
	int zPos = (invScale * p.z) / 1;

	bool isEven = (xPos + yPos + zPos) % 2 == 0;

	return isEven ? even->Value(u, v, p) : odd->Value(u, v, p);
    }

    Texture::Texture(const SolidColor solidColor) : type(SOLID) { data.solidColor = solidColor; } 
    Color Texture::Value(double u, double v, const Vec3& p) const
    {
	switch(type)
	{
	    case SOLID:
		return data.solidColor.Value(u, v, p);

	    default:
		return {0, 0, 0};
	}
    }
}
