#include "ryt/core/rtcontext.hpp"
#include "ryt/utils/gpucontextmanager.hpp"
#include <ryt/core/backend/kernelcontext.cuh>

namespace RYT {
__global__ void
InitializeKernelRaytracingContext(RaytracingContext *deviceContext) {
  int workIndexX = (blockDim.x * blockIdx.x) + threadIdx.x;
  int workIndexY = (blockDim.y * blockIdx.y) + threadIdx.y;

  KernelContext *kernelContext = deviceContext->kernelContext;

  if (workIndexX >= kernelContext->dimensionX ||
      workIndexY >= kernelContext->dimensionY)
    return;

  int workIndex = (workIndexY * kernelContext->dimensionX) + workIndexX;
  // seed - 1234 | sequence - workIndex | offset - 0 | &(states[workIndex])
  curand_init(1234, workIndex, 0, &(kernelContext->states[workIndex]));
}

KernelContext *SetupKernelContext(int dimensionX, int dimensionY,
                                  DeviceContextInfo *deviceInfo) {

  curandState *states;
  cudaMalloc(&states, dimensionX * dimensionY * sizeof(curandState));

  KernelContext localKernelContext;
  localKernelContext.dimensionX = dimensionX;
  localKernelContext.dimensionY = dimensionY;
  localKernelContext.states = states;

  KernelContext *kernelContext;
  cudaMalloc(&kernelContext, sizeof(KernelContext));
  cudaMemcpy(kernelContext, &localKernelContext, sizeof(KernelContext),
             cudaMemcpyHostToDevice);

  deviceInfo->curandStates = states;
  deviceInfo->kernelContext = kernelContext;

  return kernelContext;
}
} // namespace RYT
