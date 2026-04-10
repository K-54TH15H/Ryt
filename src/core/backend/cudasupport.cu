#include <ryt/core/backend/cudasupport.cuh>
#include <ryt/core/rtcontext.hpp>
#include <ryt/utils/framebuffer.hpp>
#include <ryt/utils/gpucontextmanager.hpp>

namespace RYT {

GPUFrameBuffer CreateFrameBufferOnGPU(int width, int height) {
  GPUFrameBuffer deviceFb;
  size_t bytes = width * height * sizeof(Color);

  cudaMalloc(&deviceFb, bytes);
  return deviceFb;
}

void DestroyFrameBufferOnGPU(GPUFrameBuffer gpuFb) { cudaFree(gpuFb); }

void CopyFrameBufferFromDeviceToHost(const GPUFrameBuffer deviceFb,
                                     FrameBuffer *fb) {
  size_t bytes = fb->GetSize() * sizeof(Color);

  cudaMemcpy((fb->GetBufferAddress()), deviceFb, bytes, cudaMemcpyDeviceToHost);
}

void LaunchKernel(const Camera &camera, const RaytracingContext *deviceContext,
                  GPUFrameBuffer deviceFb) {
  int imageWidth = camera.imgW;
  int imageHeight = camera.imgH;

  // Set up the chevron launch config
  dim3 blocks(32, 32); // 32 x 32 threads

  int gridX = (imageWidth + (blocks.x - 1)) / blocks.x;  // round up gridX
  int gridY = (imageHeight + (blocks.y - 1)) / blocks.y; // round up gridY

  dim3 grids(gridX, gridY);

  // Launch the Kernel
  RenderKernel<<<grids, blocks>>>(camera, deviceContext, deviceFb);
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

  for (int sj = 0; sj < camera.sqrtSpp; sj++) {
    for (int si = 0; si < camera.sqrtSpp; si++) {
      Ray r = camera.GetRay(j, i, si, sj);
      pixelColor += camera.RayColor(r, camera.maxDepth, deviceContext);
    }
  }
  deviceFb[(workIndexY * imageWidth) + workIndexX] =
      camera.pixelSamplesScale * pixelColor;
}
} // namespace RYT
