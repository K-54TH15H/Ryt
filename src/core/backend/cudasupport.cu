#include "ryt/core/hitrecord.hpp"
#include <cuda_runtime.h>
#include <curand_kernel.h>
#include <driver_types.h>
#include <ryt/core/backend/cudasupport.cuh>
#include <ryt/core/backend/kernelcontext.cuh>
#include <ryt/core/rtcontext.hpp>
#include <ryt/utils/framebuffer.hpp>
#include <ryt/utils/gpucontextmanager.hpp>

namespace RYT {
void LaunchKernel(const Camera &camera, RaytracingContext *deviceContext,
                  GPUFrameBuffer deviceFb) {
  int dimensionX = camera.imgW;
  int dimensionY = camera.imgH;

  // Set up the chevron launch config
  dim3 blocks(16, 16); // 16 x 16 threads

  int gridX = (dimensionX + (blocks.x - 1)) / blocks.x; // round up gridX
  int gridY = (dimensionY + (blocks.y - 1)) / blocks.y; // round up gridY

  dim3 grids(gridX, gridY);
  cudaDeviceSetLimit(cudaLimitStackSize, 8192 * 4);

  // Set up the Kernel
  InitializeKernelRaytracingContext<<<grids, blocks>>>(deviceContext);

  // Launch the Kernel
  RenderKernel<<<grids, blocks>>>(camera, deviceContext, deviceFb);

  cudaError_t err = cudaGetLastError();
  if (err != cudaSuccess)
    printf("Error: %s\n", cudaGetErrorString(err));
}

__global__ void RenderKernel(const Camera camera,
                             const RaytracingContext *deviceContext,
                             GPUFrameBuffer deviceFb) {

  int imageWidth = camera.imgW;
  int imageHeight = camera.imgH;

  int workIndexX = (blockDim.x * blockIdx.x) + threadIdx.x;
  int workIndexY = (blockDim.y * blockIdx.y) + threadIdx.y;

  // Bounds Checking - Invalid Threads
  if (workIndexX >= imageWidth || workIndexY >= imageHeight)
    return;

  Color pixelColor(0, 0, 0);
  int workIndex = (workIndexY * imageWidth) + workIndexX;
  /* -----
  Ray r = camera.GetRay(workIndexX, workIndexY, 0, 0);
  HitRecord rec;
  Interval rayT(0.001, RYT_INFINITY);

  if(HitWorld(deviceContext, r, rayT, rec))
      deviceFb[workIndex] = Color(1, 0, 0);
  else
      deviceFb[workIndex] = Color(0, 0, 1);

  return ;
  */

  curandState *state = &(deviceContext->kernelContext->states[workIndex]);

  for (int sj = 0; sj < camera.sqrtSpp; sj++) {
    for (int si = 0; si < camera.sqrtSpp; si++) {
      Ray r = camera.GetRay(workIndexX, workIndexY, si, sj, state);
      pixelColor += camera.RayColor(r, camera.maxDepth, deviceContext, state);
    }
  }
  deviceFb[workIndex] = camera.pixelSamplesScale * pixelColor;
}
} // namespace RYT
