#include <ryt/rtcore.hpp>

namespace RYT {
// Context functions
void InitializeRaytracingContext(RaytracingContext *context, size_t capacity) {
  context->hittableCapacity = capacity;
  context->hittableSize = 0;
  
  // Creates an empty bounding box
  context->bBox = AABB();
  context->hittables = new Hittable[capacity];

  context->bvhNodes = new BVHNode[2 * capacity];
  context->bvhNodeCapacity = 2 * capacity;
  context->bvhNodeSize = 0;
  context->bvhRootIndex = -1;

}

void OptimizeRaytracingContext(RaytracingContext* context)
{
    context->bvhRootIndex = ConstructBVHTree(context, 0, context->hittableSize);
}

void DestroyRaytracingContext(RaytracingContext *context) {
  delete[] context->hittables;
  delete[] context->bvhNodes;

  context->hittables = nullptr;
  context->bvhNodes = nullptr;

  context->hittableSize = 0;
  context->hittableCapacity = 0;

  context->bvhNodeSize = 0;
  context->bvhNodeCapacity = 0;
  context->bvhRootIndex = -1;
  
  // Destroys AABB by replacing  it with empty bounding box
  context->bBox = AABB(); 
}

Hittable *PushHittable(RaytracingContext *context, Hittable hittable) {
  if (context->hittableSize >= context->hittableCapacity)
    return nullptr;

  context->hittables[context->hittableSize] = hittable;
    
  context->bBox = AABB(context->bBox, hittable.bBox);
  return &(context->hittables[context->hittableSize++]);
}

bool HitWorld(const RaytracingContext *context, const Ray &r, Interval t,
              HitRecord &rec) {

  if (context->bvhRootIndex != -1)
  {
     return HitBVH(context, context->bvhRootIndex, r, t, rec);
  }

  HitRecord tempRec;
  bool hitAnything = false;
  double closestSoFar = t.max;

  // Loop through all objects of the World
  for (size_t i = 0; i < context->hittableSize; i++) {
    if ((context->hittables[i])
            .Hit(r, Interval(t.min, closestSoFar), tempRec)) {
      hitAnything = true;
      closestSoFar = tempRec.t;
      rec = tempRec;
    }
  }

  return hitAnything;
}
} // namespace RYT
