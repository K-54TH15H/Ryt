#ifndef HITTABLE_H
#define HITTABLE_H

#include <ryt/math/interval.hpp>
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

	    union MemberData
	    {
		Sphere sphere;
	
		// default constructors get destroyed placeholder constructors and destrcutors
		// manually handled via class constructors and destrcutors
		MemberData() {}
		~MemberData() {}

	    }data;
	    
	    Hittable()
	    {
		type = NONE;
	    }

	    Hittable(Sphere s)
	    {
		type = SPHERE;
		data.sphere = s;
	    }

	    ~Hittable()
	    {
		switch(type)
		{
		    case SPHERE:
			((data.sphere)).~Sphere(); // Calling Destructor Call Explicitly
			break;

		    default: // None
			break;
		}
 
	    }
	     
	    bool Hit(const Ray& r, Interval t, HitRecord& rec)
	    {
		switch(type)
		{
		    case SPHERE:
			return ((data.sphere)).Hit(r, t, rec);
			
		    default: // Hit None 
			return false;
		}	 
	    }
    };
}

#endif
