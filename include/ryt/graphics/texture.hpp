#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <ryt/graphics/color.hpp>


namespace RYT
{
    enum TextureType
    {
	SOLID,
    };

    class SolidColor
    {
	public:
	    SolidColor(const Color& albedo);
	    SolidColor(double r, double g, double b);

	    Color Value(double u, double v, const Vec3& p) const;

	private:
	    Color albedo;
    };

    class Texture
    {
	public:
	    
	private:
    };

}
#endif
