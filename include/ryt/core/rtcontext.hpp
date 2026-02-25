#ifndef RTCONTEXT_HPP
#define RTCONTEXT_HPP

#include <ryt/core/bvh.hpp>
#include <ryt/core/hittable.hpp>
#include <ryt/graphics/texture.hpp>

namespace RYT {
// ********** RAYTRACING-CONTEXT **********
struct RaytracingContext {
  Hittable *hittables;

  size_t hittableSize;
  size_t hittableCapacity;

  // BVH
  BVHNode *bvhNodes;
  size_t bvhNodeSize;
  size_t bvhNodeCapacity;

  int bvhRootIndex;

  // Textures
  Texture *textures;
  size_t textureSize;
  size_t textureCapacity;

  // bounding box for the entire context scene
  AABB bBox;
};

// Context functions
void InitializeRaytracingContext(RaytracingContext *context, size_t capacity,
                                 size_t textureCapacity);
void OptimizeRaytracingContext(RaytracingContext *context);
void DestroyRaytracingContext(RaytracingContext *context);

Hittable *PushHittable(RaytracingContext *context, Hittable hittable);
int PushTexture(RaytracingContext *context, Texture texture);

bool HitWorld(const RaytracingContext *context, const Ray &r, Interval t,
              HitRecord &rec);
} // namespace RYT

#endif
