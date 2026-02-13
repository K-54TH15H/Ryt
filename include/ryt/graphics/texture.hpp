#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <ryt/graphics/color.hpp>


namespace RYT
{
    enum TextureType
    {
	SOLID,
	CHECKER,
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

    class CheckerTexture
    {
	private:

	public:
    };

    class Texture
    {
	public:
	    // Constructors
	    Texture(SolidColor solidColor);
	    Color Value(double u, double v, const Vec3& p) const; 

	private:
	    TextureType type;
	    union MemberData
	    {
		SolidColor solidColor;

		MemberData() {}
		~MemberData() {}
	    } data;
    };

}
#endif
