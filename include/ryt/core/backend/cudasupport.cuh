#ifndef CUDASUPPORT_HPP
#define CUDASUPPORT_HPP

#include <cuda_runtime.h>

#include <ryt/core/rtcontext.hpp>
#include <ryt/utils/camera.hpp>
#include <ryt/utils/framebuffer.hpp>
#include <ryt/utils/gpucontextmanager.hpp>
#include <ryt/utils/gpuframebuffer.hpp>

namespace RYT {

struct KernelContext {
  curandState *states;
  int dimensionX; // dimension X for Kernel
  int dimensionY; // dimension Y for Kernel
};

// Create a device KernelContext
KernelContext *SetupKernelContext(int dimensionX, int dimensionY,
                                  DeviceContextInfo *deviceContext);
// Initialize the curandStates of the kernelContext
__global__ void
InitializeKernelRaytracingContext(RaytracingContext *kernelInfo);

// Manages context and launches the RenderKernel
void LaunchKernel(const Camera &camera, RaytracingContext *deviceContext,
                  GPUFrameBuffer fb);

// Retrieve results from device framebuffer into host Framebuffer
void CopyFrameBufferFromDeviceToHost(const GPUFrameBuffer deviceFb,
                                     const FrameBuffer &fb);

// The Main RenderKernel
__global__ void RenderKernel(const Camera camera,
                             const RaytracingContext *gpuContext,
                             GPUFrameBuffer deviceFb);
} // namespace RYT

#endif
