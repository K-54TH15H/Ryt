#ifndef BASE_H
#define BASE_H

#include <ryt/graphics/color.hpp>
#include <ryt/graphics/hit_record.hpp>
#include <ryt/math/ray.hpp>


namespace ryt
{
    enum MaterialType
    {
	LAMBERTIAN,
	METAL
    };

    class Lambertian
    {
	private:
	    Color albedo;

	public:
	    Lambertian(const Color& albedo) : albedo(albedo) {}

	    bool Scatter(const Ray& rIn, const HitRecord& rec, Color& attenuation, Ray& scattered) const
	    {
		Vec3 scatter_direction = rec.normal + RandomUnitVector();

		if(scatter_direction.NearZero()) scatter_direction = rec.normal;

		scattered = Ray(rec.p, scatter_direction);
		attenuation = albedo;

		return true;
	    }
    };

    class Metal
    {
	private:
	    Color albedo;
	    double fuzz;

	public:
	    Metal(const Color& albedo, double fuzz) : albedo(albedo), fuzz(fuzz) {}

	    bool Scatter(const Ray& rIn, const HitRecord& rec, Color& attenuation, Ray& scattered) const 
	    {
		Vec3 reflected = Reflect(rIn.Direction(), rec.normal);
		reflected = (UnitVector(reflected)) + (fuzz * RandomUnitVector());

		scattered = Ray(rec.p, reflected);
		attenuation = albedo;

		return (Dot(scattered.Direction(), rec.normal) > 0);
	    }
    };

    class Material
    {
	private:
	    MaterialType type;

	    union MemberData 
	    {
		Lambertian lambertian;
		Metal metal;

		MemberData() {}
		~MemberData() {}

	    } data;

	public:

	    Material(const Lambertian lambertian) : type(LAMBERTIAN)
	    {
		data.lambertian = lambertian;
	    }

	    Material(const Metal metal) : type(METAL)
	    {
		data.metal = metal;
	    }

	    ~Material()
	    {
		switch(type)
		{
		    case LAMBERTIAN:
			(data.lambertian).~Lambertian();
			break;
		    
		    case METAL:
			(data.metal).~Metal();
			break;
		}
	    }

	    bool Scatter(const Ray& rIn, const HitRecord& rec, Color& attenuation, Ray& scattered) const 
	    {
		switch(type)
		{
		    case LAMBERTIAN:
			return data.lambertian.Scatter(rIn, rec, attenuation, scattered);

		    case METAL:
			return data.metal.Scatter(rIn, rec, attenuation, scattered);

		    default:
			return false;
		}
	    }
    };
}

#endif
