#include <cuda_runtime.h>
#include <ryt/utils/gpuframebuffer.hpp>

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

  cudaMemcpy(*(fb->GetBufferAddress()), deviceFb, bytes,
             cudaMemcpyDeviceToHost);
}
} // namespace RYT
