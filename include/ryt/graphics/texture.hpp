#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <ryt/graphics/color.hpp>


namespace RYT
{
    class Texture;

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
	    double invScale;
	    Texture* even;
	    Texture* odd;

	public:
	    CheckerTexture(double scale, Texture* even, Texture* odd);
	    CheckerTexture(double scale, const Color& c1, const Color& c2);

	    Color Value(double u, double v, const Vec3& p) const;
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
