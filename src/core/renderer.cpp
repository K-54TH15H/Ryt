#include <cuda_runtime_api.h>
#include <driver_types.h>
#include <ryt/core/backend/cudasupport.cuh>
#include <ryt/core/renderer.hpp>
#include <ryt/core/rtcontext.hpp>
#include <ryt/utils/gpucontextmanager.hpp>
#include <ryt/utils/gpuframebuffer.hpp>
#include <omp.h>

namespace RYT {
Renderer::Renderer(RenderMode mode) : mode(mode) {}
Renderer::~Renderer() {}

void Renderer::Render(Camera &camera, RaytracingContext *context) const {
  camera.Initialize();
  FrameBuffer frameBuffer(camera.imgW, camera.imgH);

  if (mode == RenderMode::CPU)
    RenderCPU(camera, context, frameBuffer);
  else
    RenderGPU(camera, context, frameBuffer);

  frameBuffer.WriteToPPM(std::cout);
  std::clog << std::endl << "Render Complete" << std::endl;
}

void Renderer::SetMode(RenderMode mode) { this->mode = mode; }

void Renderer::RenderCPU(const Camera &camera, RaytracingContext *context,
                         FrameBuffer &frameBuffer) {

  // Initialize context backend
  context->renderMode = RenderMode::CPU;
  context->kernelContext = nullptr;

#pragma omp parallel for collapse(2) schedule(guided)
  for (int i = 0; i < camera.imgH; i++) {
    for (int j = 0; j < camera.imgW; j++) {
      Color pixelColor(0, 0, 0);
      for (int sj = 0; sj < camera.sqrtSpp; sj++) {
        for (int si = 0; si < camera.sqrtSpp; si++) {
          Ray r = camera.GetRay(j, i, si, sj);
          pixelColor += camera.RayColor(r, camera.maxDepth, context);
        }
      }
      frameBuffer.WriteToBuffer(camera.pixelSamplesScale * pixelColor, i, j);
    }
  }
}

void Renderer::RenderGPU(const Camera &camera, RaytracingContext *hostContext,
                         FrameBuffer &fb) {

  int imageWidth = camera.imgW;
  int imageHeight = camera.imgH;

  GPUContextManager gpuContextManager;
  gpuContextManager.Upload(hostContext, imageWidth, imageHeight);

  GPUFrameBuffer deviceFb = CreateFrameBufferOnGPU(imageWidth, imageHeight);
  RaytracingContext *deviceContext = gpuContextManager.deviceContext;

  // Launch Render Kernel
  LaunchKernel(camera, deviceContext, deviceFb);

  // Synchronize with Device
  // to retrieve finishded results
  cudaError_t err = cudaDeviceSynchronize();
  if (err != cudaSuccess)
    printf("Kernel Error: %s\n", cudaGetErrorString(err));
  // Retrieve results
  CopyFrameBufferFromDeviceToHost(deviceFb, &fb);
}
} // namespace RYT
