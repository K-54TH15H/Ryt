#ifndef KERNELCONTEXT_CUH
#define KERNELCONTEXT_CUH

#include "ryt/utils/gpucontextmanager.hpp"
#include <curand_kernel.h>
#include <ryt/core/rtcontext.hpp>

namespace RYT {
struct KernelContext {
  curandState *states;
  int dimensionX; // dimension X for Kernel
  int dimensionY; // dimension Y for Kernel
};

KernelContext *SetupKernelContext(int dimensionX, int dimensionY,
                                  DeviceContextInfo *deviceContext);
__global__ void
InitializeKernelRaytracingContext(RaytracingContext *kernelInfo);
} // namespace RYT
#endif
