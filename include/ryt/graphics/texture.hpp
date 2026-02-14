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

    class SolidTexture
    {
	public:
	    SolidTexture(const Color& albedo);
	    SolidTexture(double r, double g, double b);

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
	    // CheckerTexture(double scale, const Color& c1, const Color& c2);

	    Color Value(double u, double v, const Vec3& p) const;
    };

    class Texture
    {
	public:
	    // Constructors
	    Texture(const SolidTexture solidTexture);
	    Texture(const CheckerTexture checkerTexture);
	    Texture(const Color color);

	    Color Value(double u, double v, const Vec3& p) const; 

	private:
	    TextureType type;
	    union MemberData
	    {
		SolidTexture solidTexture;
		CheckerTexture checkerTexture;

		MemberData() {}
		~MemberData() {}
	    } data;
    };
}
#endif
