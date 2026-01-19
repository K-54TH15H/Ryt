#ifndef MATERIAL_H
#define MATERIAL_H

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

    struct Lambertian
    {
	Color albedo;
    };

    struct Metal
    {
	Color albedo;
        double roughness;
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
	    
	    bool ScatterLambertian(const Ray& rIn, const HitRecord& rec, Color& attenuation, Ray& scattered) const
	    {
		Vec3 scatterDirection = rec.normal + RandomUnitVector();

		if(scatterDirection.NearZero()) scatterDirection = rec.normal;

		scattered = Ray(rec.p, scatterDirection);
		attenuation = data.lambertian.albedo;

		return true;
	    }

	    bool ScatterMetal(const Ray& rIn, const HitRecord& rec, Color& attenuation, Ray& scattered) const
	    {
		Vec3 reflected = Reflect(rIn.Direction(), rec.normal);
		reflected = (UnitVector(reflected)) + (data.metal.roughness * RandomUnitVector());

		scattered = Ray(rec.p, reflected);
		attenuation = data.metal.albedo;

		return (Dot(scattered.Direction(), rec.normal) > 0);

	    }

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
			return this->ScatterLambertian(rIn, rec, attenuation, scattered);

		    case METAL:
			return this->ScatterMetal(rIn, rec, attenuation, scattered);

		    default:
			return false;
		}
	    }
    };
}

#endif
