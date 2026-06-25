#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <device_types.h>
#include <ryt/core/rtcontext.hpp>
#include <ryt/utils/gpuframebuffer.hpp>

namespace RYT {

// ********** Camera ********** //
class Camera {
public:
  // Setters
  void SetLookFrom(Vec3 location);
  void SetLookAt(Vec3 location);
  void SetFov(double fov);
  void SetSamplesPerPixels(int n);
  void SetMaxDepth(int n);
  void SetDefocusAngle(double degree);
  void SetFocusDistance(double distance);
  void SetBackGroundColor(Color color);

  // Friend class and functions which
  // are allowed to access private data of camera
  friend class Renderer;
  friend void LaunchKernel(const Camera &camera,
                           RaytracingContext *deviceContext,
                           GPUFrameBuffer devicefB);
  friend __global__ void RenderKernel(const Camera camera,
                                      const RaytracingContext *deviceContext,
                                      GPUFrameBuffer deviceFb);

private:
  double aspectRatio; // Ratio of image width to height
  int imgW;           // Rendered image width
  int imgH;           // Rendered image height

  Vec3 center;                   // Camera center
  Vec3 lookFrom = Vec3(0, 0, 0); // Look from a point | default : [0, 0, 0]
  Vec3 lookAt = Vec3(0, 0, -1);  // Look at a point | default : [0, 0, -1]

  Vec3 u, v, w; // Relative camera frame basis

  Vec3 pixel00Loc;  // Location of pixel - [0, 0]
  Vec3 pixelDeltaU; // Offset for pixel to the right
  Vec3 pixelDeltaV; // Offset for pixel to the bottom

  int samplesPerPixels = 10; // Count of random samples per pixels
  double pixelSamplesScale;
  int maxDepth = 10;   // Maximum no of Ray bounces into scene
  int sqrtSpp;         // Square root of number of samples per pixel
  double recipSqrtSpp; // 1 / sqrtSpp

  double vFov = 90; // vertical view angle - FOV | default : [90]

  Color backGround; // background color if no ray hits

  double defocusAngle = 0;
  double focusDistance = 10;
  Vec3 defocusDiskU;
  Vec3 defocusDiskV;

  __host__ void Initialize();
  __host__ __device__ Vec3 SampleSquare(curandState *state = nullptr) const;

  // Constructs a camera Ray from origin to a randomly sampled pt i, j
  __host__ __device__ Ray GetRay(int i, int j, int si, int sj,
                                 curandState *state = nullptr) const;
  __host__ __device__ Color RayColor(const Ray &r, int depth,
                                     const RaytracingContext *world,
                                     curandState *state = nullptr) const;

  __host__ __device__ Vec3
  DefocusDiskSample(curandState *state = nullptr) const;
  __host__ __device__ Vec3
  SampleSquareStratified(int si, int sj, curandState *state = nullptr) const;
};
} // namespace RYT

#endif
