#ifndef HITTABLE_H
#define HITTABLE_H

#include <ryt/math/ray.hpp>
#include <ryt/graphics/sphere.hpp>

namespace ryt
{
    // Tag for Geometry type
    enum GeometryType
    {
	SPHERE,
	NONE
    };

    class Hittable
    {

	public:
	    GeometryType type;

	    union data
	    {
		Sphere sphere;
	
		// default constructors get destroyed placeholder constructors and destrcutors
		// manually handled via class constructors and destrcutors
		data() {}
		~data() {}

	    } Data;
	    
	    Hittable()
	    {
		type = NONE;
	    }

	    Hittable(Sphere s)
	    {
		type = SPHERE;
		Data.sphere = s;
	    }

	    ~Hittable()
	    {
		switch(type)
		{
		    case SPHERE:
			((Data.sphere)).~Sphere(); // Calling Destructor Call Explicitly
			break;

		    default: // None
			break;
		}
 
	    }
	     
	    bool hit(const ray& r, double ray_tmin, double ray_tmax, Hit_Record& rec)
	    {
		switch(type)
		{
		    case SPHERE:
			return ((Data.sphere)).hit(r, ray_tmin, ray_tmax, rec);
			
		    default: // Hit None 
			return false;
		}	 
	    }
    };
}

#endif
