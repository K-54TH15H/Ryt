#include "ryt/graphics/texture.hpp"
#include <driver_types.h>
#include <ryt/core/cudasupport.cuh>
#include <ryt/core/rtcontext.hpp>

namespace RYT {
RaytracingContext *CreateContextOnGPU(const RaytracingContext *context) {
  RaytracingContext *gpuContext;

  // Stage a local context and copy this
  // staged context onto gpuContext
  RaytracingContext stagedContext;
  cudaMalloc(&gpuContext, sizeof(RaytracingContext));

  // set up device field;
  Hittable *gpuHittables;
  BVHNode *gpuBvhNodes;
  Material *gpuMaterials;
  Texture *gpuTextures;
  Image *gpuImages;

  // temp variable for bytes to copy
  size_t bytes;

  // Hittables
  bytes = sizeof(Hittable) * context->hittableCapacity;
  cudaMalloc(&gpuHittables, bytes);
  cudaMemcpy(gpuHittables, context->hittables, bytes, cudaMemcpyHostToDevice);
  // BVH Nodes
  bytes = sizeof(BVHNode) * context->bvhNodeCapacity;
  cudaMalloc(&gpuBvhNodes, bytes);
  cudaMemcpy(gpuBvhNodes, context->bvhNodes, bytes, cudaMemcpyHostToDevice);
  // Materials
  bytes = sizeof(Material) * context->materialCapacity;
  cudaMalloc(&gpuMaterials, bytes);
  cudaMemcpy(gpuMaterials, context->materials, bytes, cudaMemcpyHostToDevice);
  // Textures
  bytes = sizeof(Texture) * context->textureSize;
  cudaMalloc(&gpuMaterials, bytes);
  cudaMemcpy(gpuTextures, context->textures, bytes, cudaMemcpyHostToDevice);
  // Images -- To be modified
  bytes = sizeof(Image) * context->imageCapacity;
  cudaMalloc(&gpuImages, bytes);
  cudaMemcpy(gpuImages, context->images, bytes, cudaMemcpyHostToDevice);

  // Plug the device fields to the gpuContext
  stagedContext.hittables = gpuHittables;
  stagedContext.hittableSize = context->hittableSize;
  stagedContext.hittableCapacity = context->hittableCapacity;

  stagedContext.bvhNodes = gpuBvhNodes;
  stagedContext.bvhNodeSize = context->bvhNodeSize;
  stagedContext.bvhNodeCapacity = context->bvhNodeCapacity;
  stagedContext.bvhRootIndex = context->bvhRootIndex;

  stagedContext.materials = gpuMaterials;
  stagedContext.materialSize = context->materialSize;
  stagedContext.materialCapacity = context->materialCapacity;

  stagedContext.textures = gpuTextures;
  stagedContext.textureSize = context->textureSize;
  stagedContext.textureCapacity = context->bvhNodeCapacity;

  stagedContext.images = gpuImages;
  stagedContext.imageSize = context->imageSize;
  stagedContext.imageCapacity = context->imageCapacity;

  stagedContext.bBox = context->bBox;

  cudaMemcpy(&stagedContext, gpuContext, sizeof(RaytracingContext),
             cudaMemcpyHostToDevice);

  return gpuContext;
}
} // namespace RYT
