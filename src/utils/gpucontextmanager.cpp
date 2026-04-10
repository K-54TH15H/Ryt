#include <cuda_runtime.h>
#include <driver_types.h>
#include <ryt/utils/gpucontextmanager.hpp>

namespace RYT {
GPUContextManager::GPUContextManager() {}
GPUContextManager::~GPUContextManager() { Erase(); }

void GPUContextManager::Upload(const RaytracingContext *hostContext) {
  if (hostContext == NULL)
    return;

  Erase();
  RaytracingContext localContext;

  // Hittables
  AllocateAndCopy(&deviceInfo.hittables, hostContext->hittables,
                  hostContext->hittableCapacity);
  localContext.hittables = deviceInfo.hittables;
  localContext.hittableSize = hostContext->hittableSize;
  localContext.hittableCapacity = hostContext->hittableCapacity;

  // BVH Nodes
  AllocateAndCopy(&deviceInfo.bvhNodes, hostContext->bvhNodes,
                  hostContext->bvhNodeCapacity);
  localContext.bvhNodes = deviceInfo.bvhNodes;
  localContext.bvhNodeSize = hostContext->bvhNodeSize;
  localContext.bvhNodeCapacity = hostContext->bvhNodeCapacity;

  // Materials
  AllocateAndCopy(&deviceInfo.materials, hostContext->materials,
                  hostContext->materialCapacity);
  localContext.materials = deviceInfo.materials;
  localContext.materialSize = hostContext->materialSize;
  localContext.materialCapacity = hostContext->materialCapacity;

  // Textures
  AllocateAndCopy(&deviceInfo.textures, hostContext->textures,
                  hostContext->textureCapacity);
  localContext.textures = deviceInfo.textures;
  localContext.textureSize = hostContext->textureSize;
  localContext.textureCapacity = hostContext->textureCapacity;

  // Images
  AllocateImages(hostContext);
  localContext.images = deviceInfo.images;
  localContext.imageSize = hostContext->imageSize;
  localContext.imageCapacity = hostContext->imageCapacity;

  cudaMalloc(&deviceContext, sizeof(RaytracingContext));
  cudaMemcpy(deviceContext, &localContext, sizeof(RaytracingContext),
             cudaMemcpyHostToDevice);
}

void GPUContextManager::Erase() {
  if (deviceContext) {
    cudaFree(deviceContext);
    deviceContext = nullptr;
  }
  if (deviceInfo.hittables) {
    cudaFree(deviceInfo.hittables);
    deviceInfo.hittables = nullptr;
  }
  if (deviceInfo.bvhNodes) {
    cudaFree(deviceInfo.bvhNodes);
    deviceInfo.bvhNodes = nullptr;
  }
  if (deviceInfo.materials) {
    cudaFree(deviceInfo.materials);
    deviceInfo.materials = nullptr;
  }
  if (deviceInfo.textures) {
    cudaFree(deviceInfo.textures);
    deviceInfo.textures = nullptr;
  }
  if (deviceInfo.images) {
    cudaFree(deviceInfo.images);
    deviceInfo.images = nullptr;
  }

  for (size_t index = 0; index < deviceInfo.imageData.size(); index++)
    cudaFree(deviceInfo.imageData[index]);

  deviceInfo.imageData.clear();
}

template <typename T>
void GPUContextManager::AllocateAndCopy(T **devicePtr, T *hostPtr,
                                        size_t count) {
  if (hostPtr == NULL || count == 0 || devicePtr == NULL)
    return;

  size_t bytes = sizeof(T) * count;

  cudaMalloc(devicePtr, bytes);
  cudaMemcpy(*devicePtr, hostPtr, bytes, cudaMemcpyHostToDevice);
}

void GPUContextManager::AllocateImages(const RaytracingContext *hostContext) {
  if (hostContext == NULL || hostContext->imageSize <= 0)
    return;

  size_t bytes;
  Image *localImages = new Image[hostContext->imageSize];

  // Deep copy all image's float and byte data
  for (size_t imageIndex = 0; imageIndex < hostContext->imageSize;
       imageIndex++) {
    // To DeepCopy hostContext[imageIndex] to localImages[imageIndex]
    Image &localImage = localImages[imageIndex];
    const Image &hostImage = hostContext->images[imageIndex];

    localImage.imageWidth = hostImage.imageWidth;
    localImage.imageHeight = hostImage.imageHeight;
    localImage.bytesPerScanline = hostImage.bytesPerScanline;

    size_t pixelCount = hostImage.imageWidth * hostImage.imageHeight;

    // Copy float data
    if (hostImage.HasFloatData()) {
      bytes = pixelCount * 3 * sizeof(float);
      float *lfdata; // local float data

      cudaMalloc(&lfdata, bytes);
      cudaMemcpy(lfdata, hostImage.fdata, bytes, cudaMemcpyHostToDevice);

      deviceInfo.imageData.push_back((void *)lfdata);
      localImage.fdata = lfdata;
    }
    // Copy binary data
    if (hostImage.HasBinaryData()) {
      bytes = pixelCount * 3 * sizeof(unsigned char);
      unsigned char *lbdata; // local float data

      cudaMalloc(&lbdata, bytes);
      cudaMemcpy(lbdata, hostImage.bdata, bytes, cudaMemcpyHostToDevice);

      deviceInfo.imageData.push_back((void *)lbdata);
      localImage.bdata = lbdata;
    }
  }

  bytes = sizeof(Image) * hostContext->imageSize;
  cudaMalloc(&deviceInfo.images, bytes);
  cudaMemcpy(deviceInfo.images, localImages, bytes, cudaMemcpyHostToDevice);

  // Set float and binary data to null for the localContext
  // after copy as it refers to gpu address space
  for (size_t imageIndex = 0; imageIndex < hostContext->imageSize;
       imageIndex++) {
    localImages[imageIndex].fdata = nullptr;
    localImages[imageIndex].bdata = nullptr;
  }

  delete[] localImages;
}
} // namespace RYT
