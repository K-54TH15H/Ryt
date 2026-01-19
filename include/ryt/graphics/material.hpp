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
	    color albedo;

	public:
	    Lambertian(const color& albedo) : albedo(albedo) {}

	    bool scatter(const Ray& r_in, const Hit_Record& rec, color& attenuation, Ray& scattered) const
	    {
		Vec3 scatter_direction = rec.normal + random_unit_vector();

		if(scatter_direction.near_zero()) scatter_direction = rec.normal;

		scattered = Ray(rec.p, scatter_direction);
		attenuation = albedo;

		return true;
	    }
    };

    class Metal
    {
	private:
	    color albedo;
	    double fuzz;

	public:
	    Metal(const color& albedo, double fuzz) : albedo(albedo), fuzz(fuzz) {}

	    bool scatter(const Ray& r_in, const Hit_Record& rec, color& attenuation, Ray& scattered) const 
	    {
		Vec3 reflected = reflect(r_in.direction(), rec.normal);
		reflected = (unit_vector(reflected)) + (fuzz * random_unit_vector());

		scattered = Ray(rec.p, reflected);
		attenuation = albedo;

		return (dot(scattered.direction(), rec.normal) > 0);
	    }
    };

    class Material
    {
	private:
	    MaterialType type;

	    union data 
	    {
		Lambertian lambertian;
		Metal metal;

		data() {}
		~data() {}

	    } Data;

	public:

	    Material(const Lambertian lambertian) : type(LAMBERTIAN)
	    {
		Data.lambertian = lambertian;
	    }

	    Material(const Metal metal) : type(METAL)
	    {
		Data.metal = metal;
	    }

	    ~Material()
	    {
		switch(type)
		{
		    case LAMBERTIAN:
			(Data.lambertian).~Lambertian();
			break;
		    
		    case METAL:
			(Data.metal).~Metal();
			break;
		}
	    }

	    bool scatter(const Ray& r_in, const Hit_Record& rec, color& attenuation, Ray& scattered) const 
	    {
		switch(type)
		{
		    case LAMBERTIAN:
			return Data.lambertian.scatter(r_in, rec, attenuation, scattered);

		    case METAL:
			return Data.metal.scatter(r_in, rec, attenuation, scattered);

		    default:
			return false;
		}
	    }
    };
}

#endif
