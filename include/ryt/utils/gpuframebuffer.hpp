#include <ryt/graphics/color.hpp>
#include <ryt/utils/framebuffer.hpp>

namespace RYT {
typedef Color *GPUFrameBuffer;

GPUFrameBuffer CreateFrameBufferOnGPU(int width, int height);
void DestroyFrameBufferOnGPU(FrameBuffer *gpuFb);
void CopyFrameBufferFromDeviceToHost(const GPUFrameBuffer deviceFb,
                                     FrameBuffer *fb);
} // namespace RYT
