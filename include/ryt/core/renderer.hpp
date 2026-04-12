#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <ryt/core/rtcontext.hpp>
#include <ryt/utils/camera.hpp>
#include <ryt/utils/framebuffer.hpp>

namespace RYT {
// Renderer Class
class Renderer {
public:
  Renderer(RenderMode mode =
               RenderMode::CPU); // Constructer of renderer, default = CPU
  ~Renderer();

  // The rendering function which renders given context from camera
  void Render(Camera &camera, RaytracingContext *context) const;

  // Setters
  void SetMode(RenderMode mode);
  RenderMode GetMode() const;

private:
  RenderMode mode; // Rendering backend mode

  // Internal Backend Executors
  static void RenderCPU(const Camera &camera, RaytracingContext *context,
                        FrameBuffer &frameBuffer);
  static void RenderGPU(const Camera &camera, RaytracingContext *context,
                        FrameBuffer &frameBuffer);
};
} // namespace RYT
#endif
