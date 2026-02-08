#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <ryt/core/hitrecord.hpp>
#include <ryt/core/rtcontext.hpp>
#include <ryt/graphics/color.hpp>
#include <ryt/math/ray.hpp>

namespace RYT {

// ********** Camera ********** //
class Camera {
public:
  void Render(const RaytracingContext *world);

  // Setters
  void SetLookFrom(Vec3 location);
  void SetLookAt(Vec3 location);
  void SetFov(double fov);
  void SetSamplesPerPixels(int n);
  void SetMaxDepth(int n);
  void SetDefocusAngle(double degree);
  void SetFocusDistance(double distance);

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
  int maxDepth = 10; // Maximum no of Ray bounces into scene

  double vFov = 90; // vertical view angle - FOV | default : [90]

  double defocusAngle = 0;
  double focusDistance = 10;
  Vec3 defocusDiskU;
  Vec3 defocusDiskV;

  void Initialize();
  Vec3 SampleSquare() const;

  // Constructs a camera Ray from origin to a randomly sampled pt i, j
  Ray GetRay(int i, int j) const;
  Color RayColor(const Ray &r, int depth, const RaytracingContext *world) const;

  Vec3 DefocusDiskSample() const;
};
} // namespace RYT

#endif
