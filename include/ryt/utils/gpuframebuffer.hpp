#include <ryt/graphics/color.hpp>
#include <ryt/utils/framebuffer.hpp>

namespace RYT {
typedef Color *GPUFrameBuffer;

GPUFrameBuffer CreateFrameBufferOnGPU(int width, int height);
void DestroyFrameBufferOnGPU(FrameBuffer *gpuFb);

} // namespace RYT
