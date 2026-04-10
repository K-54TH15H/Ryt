#ifndef GPU_CONTEXTMANAGER_HPP
#define GPU_CONTEXTMANAGER_HPP
#include <ryt/core/rtcontext.hpp>
#include <vector>

namespace RYT {
struct DeviceContextInfo {
  Hittable *hittables = nullptr;
  BVHNode *bvhNodes = nullptr;
  Material *materials = nullptr;
  Texture *textures = nullptr;
  Image *images = nullptr;

  std::vector<void *> imageData;
};

class GPUContextManager {
public:
  RaytracingContext *deviceContext = nullptr;
  DeviceContextInfo deviceInfo;

  GPUContextManager();
  ~GPUContextManager();

  void Upload(const RaytracingContext *context);
  void Erase();

private:
  template <typename T>
  void AllocateAndCopy(T **devicePtr, T *hostPtr, size_t count);
  void AllocateImages(const RaytracingContext *context);
};
} // namespace RYT
#endif
