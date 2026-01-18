#ifndef CORE_H
#define CORE_H

#include <ryt/graphics/hit_record.hpp>
#include <ryt/graphics/color.hpp>

#include <ryt/math/ray.hpp>

namespace ryt
{
    class Lambertian
    {
	private:
	    color albedo;

	public:
	    Lambertian(const color& albedo) : albedo(albedo) {}

	    bool scatter(const ray& r_in, const Hit_Record& rec, color& attenuation, ray& scattered) const
	    {
		vec3 scatter_direction = rec.normal + random_unit_vector();

		if(scatter_direction.near_zero()) scatter_direction = rec.normal;

		scattered = ray(rec.p, scatter_direction);
		attenuation = albedo;

		return true;
	    }
    };

    class Metal
    {
	private:
	    color albedo;
	
	public:
	    Metal(const color& albedo) : albedo(albedo) {}

	    bool scatter(const ray& r_in, const Hit_Record& rec, color& attenuation, ray& scattered) const 
	    {
		vec3 reflected = reflect(r_in.direction(), rec.normal);
		scattered = ray(rec.p, reflected);
		attenuation = albedo;
		
		return true;
	    }
    };
}

#endif
