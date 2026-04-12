#ifndef CUDASUPPORT_HPP
#define CUDASUPPORT_HPP

#include <cuda_runtime.h>

#include <ryt/core/rtcontext.hpp>
#include <ryt/utils/camera.hpp>
#include <ryt/utils/framebuffer.hpp>
#include <ryt/utils/gpuframebuffer.hpp>

namespace RYT {

void LaunchKernel(const Camera &camera, RaytracingContext *deviceContext,
                  GPUFrameBuffer fb);

void CopyFrameBufferFromDeviceToHost(const GPUFrameBuffer deviceFb,
                                     const FrameBuffer &fb);

__global__ void RenderKernel(const Camera camera,
                             const RaytracingContext *gpuContext,
                             GPUFrameBuffer deviceFb);
} // namespace RYT

#endif
