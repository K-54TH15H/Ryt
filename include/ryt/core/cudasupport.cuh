#ifndef CUDASUPPORT_HPP
#define CUDASUPPORT_HPP

#include <cuda_runtime.h>

#include <ryt/core/rtcontext.hpp>
#include <ryt/utils/camera.hpp>
#include <ryt/utils/framebuffer.hpp>

namespace RYT {
RaytracingContext *CreateContextOnGPU(const RaytracingContext *context);
void DestroyContextOnGPU(RaytracingContext *context);

FrameBuffer *CreateFrameBufferOnGPU(int width, int height);
void DestroyFrameBufferOnGPU(FrameBuffer *gpuFb);

void LaunchRenderKerenel(const Camera &camera, const RaytracingContext *context,
                         FrameBuffer *fb);

void CopyFrameBufferFromDeviceToHost(const FrameBuffer *gpuFb,
                                     const FrameBuffer *fb);

__global__ void RenderKernel(const Camera &camera,
                             const RaytracingContext *gpuContext,
                             FrameBuffer *gpuFb);
} // namespace RYT

#endif
