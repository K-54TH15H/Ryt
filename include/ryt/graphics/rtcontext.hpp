#ifndef RTCONTEXT_H
#define RTCONTEXT_H

#include <ryt/graphics/hit_record.hpp>
#include <ryt/graphics/hittable.hpp>

#include <ryt/math/interval.hpp>

namespace ryt
{
    struct RaytracingContext
    {
	Hittable* hittables;
	size_t hittableSize;
	size_t hittableCapacity;
    };
    
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

    inline bool HitWorld(const RaytracingContext* context, const Ray& r, Interval t, HitRecord& rec)
    {	
	HitRecord tempRec;
	bool hitAnything = false;
	double closestSoFar = t.max;
	
	// Loop through all objects of the World
	for(size_t i = 0; i < context->hittableSize; i++)
	{
	    if((context->hittables[i]).Hit(r, Interval(t.min, closestSoFar), tempRec))
	    {
		hitAnything = true;
		closestSoFar = tempRec.t;
		rec = tempRec;
	    }
	}

	return hitAnything;
    }
}
#endif
