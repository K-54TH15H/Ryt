#include <ryt/core/bvh.hpp>
#include <ryt/core/rtcontext.hpp>
#include <ryt/graphics/texture.hpp>

namespace RYT {
// Context functions
void InitializeRaytracingContext(RaytracingContext *context, size_t capacity,
                                 size_t textureCapacity, size_t imageCapacity) {
  context->hittableCapacity = capacity;
  context->hittableSize = 0;

  // Creates an empty bounding box
  context->bBox = AABB();
  context->hittables = new Hittable[capacity];

  context->bvhNodes = new BVHNode[2 * capacity];
  context->bvhNodeCapacity = 2 * capacity;
  context->bvhNodeSize = 0;
  context->bvhRootIndex = -1;

  // Textures
  context->textureCapacity = textureCapacity;
  context->textures = new Texture[textureCapacity];
  context->textureSize = 0;

  // Images
  context->imageCapacity = imageCapacity;
  context->imageSize = 0;
  context->images = new Image[imageCapacity];
}

void OptimizeRaytracingContext(RaytracingContext *context) {
  context->bvhRootIndex = ConstructBVHTree(context, 0, context->hittableSize);
}

void DestroyRaytracingContext(RaytracingContext *context) {
  delete[] context->hittables;
  delete[] context->bvhNodes;
  delete[] context->textures;

  context->hittables = nullptr;
  context->bvhNodes = nullptr;

  context->hittableSize = 0;
  context->hittableCapacity = 0;

  context->bvhNodeSize = 0;
  context->bvhNodeCapacity = 0;
  context->bvhRootIndex = -1;

  context->textureCapacity = 0;
  context->textureSize = 0;

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

int PushTexture(RaytracingContext *context, Texture texture) {
  if (context->textureSize >= context->textureCapacity)
    return -1;

  int textureId = (int)context->textureSize++;
  context->textures[textureId] = texture;

  return textureId;
}

int PushImage(RaytracingContext *context, const char *cFileName) {
  int imageId = (int)context->imageSize;
  if (context->images[imageId].Load(cFileName)) {
    context->imageSize++;
    return imageId;
  } else {
    std::cerr << "[Error]: Failed to push/load image" << std::endl;
    return -1;
  }
}

bool HitWorld(const RaytracingContext *context, const Ray &r, Interval t,
              HitRecord &rec) {

  // Store context
  rec.context = context;

  if (context->bvhRootIndex != -1) {
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
