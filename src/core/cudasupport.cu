#include "ryt/core/cudasupport.cuh"
#include <ryt/core/rtcontext.hpp>

namespace RYT {
RaytracingContext *CreateContextOnGPU(const RaytracingContext *context) {
  return nullptr;
}

void DestroyContextOnGPU(RaytracingContext *gpuContext) {}

FrameBuffer *CreateFrameBufferOnGPU(int width, int height) { return nullptr; }

void DestroyFrameBufferOnGPU(FrameBuffer *fb) {}

void LaunchRenderKerenel(const Camera &camera,
                         const RaytracingContext *gpuContext, FrameBuffer *fb) {

}

__global__ void RenderKernel(const Camera &camera,
                             const RaytracingContext *gpuContext,
                             FrameBuffer *fb) {}
} // namespace RYT
