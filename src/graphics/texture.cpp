#include <ryt/graphics/texture.hpp>

namespace RYT
{
    SolidColor::SolidColor(const Color& albedo) : albedo(albedo) {}
    SolidColor::SolidColor(double r, double g, double b) : SolidColor(Color(r, g, b)) {}
    Color SolidColor::Value(double u, double v, const Vec3& p) const { return albedo; }
    
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
