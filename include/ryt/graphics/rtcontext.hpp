#ifndef RTCONTEXT_H
#define RTCONTEXT_H

#include <limits>
#include <ryt/graphics/hit_record.hpp>
#include <ryt/graphics/hittable.hpp>

namespace ryt
{
    struct RaytracingContext
    {
	Hittable* hittables;
	size_t hittableSize;
	size_t hittableCapacity;
    };
    
    // Context Constants
    const double infinity = std::numeric_limits<double>::infinity();
    const double pi = 3.1415926535897932385;

    // Context functions
    inline void InitializeRaytracingContext(RaytracingContext* context, size_t capacity)
    {
	context->hittableCapacity = capacity;
	context->hittableSize = 0;

	context->hittables = new Hittable[capacity];
    }
    
    inline void DestroyRaytracingContext(RaytracingContext* context)
    {
	delete[] context->hittables;
	context->hittableSize = 0;
	context->hittableCapacity = 0;
    }

    inline Hittable* PushHittable(RaytracingContext* context, Hittable hittable)
    {
	if(context->hittableSize >= context->hittableCapacity) return nullptr;

	context->hittables[context->hittableSize] = hittable;
	
	return &(context->hittables[context->hittableSize++]);
    }

    inline bool HitWorld(const RaytracingContext* context, const ray& r, double ray_tmin, double ray_tmax, Hit_Record& rec)
    {	
	Hit_Record temp_rec;
	bool hit_anything = false;
	double closest_so_far = ray_tmax;
	
	// Loop through all objects of the World
	for(size_t i = 0; i < context->hittableSize; i++)
	{
	    if((context->hittables[i]).hit(r, ray_tmin, closest_so_far, temp_rec))
	    {
		hit_anything = true;
		closest_so_far = temp_rec.t;
		rec = temp_rec;
	    }
	}

	return hit_anything;
    }
}
#endif
