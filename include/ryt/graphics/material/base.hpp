#ifndef BASE_H
#define BASE_H

#include <ryt/graphics/material/mcore.hpp>
#include <ryt/graphics/color.hpp>

#include <ryt/math/ray.hpp>


namespace ryt
{
    enum MaterialType
    {
	LAMBERTIAN,
	METAL
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
		
	    }
	    
	    bool scatter(const ray& r_in, const Hit_Record& rec, color& attenuation, ray& scattered) const 
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
