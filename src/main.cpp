#include <chrono>
#include <cmath>
#include <ryt/rtcore.hpp>

void RenderDefaultScene() {
  RYT::RaytracingContext world;
  RYT::InitializeRaytracingContext(&world, 16);

  RYT::Lambertian materialGround = {RYT::Color(0.8, 0.8, 0.0)};
  RYT::Lambertian materialCenter = {RYT::Color(0.2, 0.1, 0.7)};
  RYT::Metal metalLeft = {RYT::Color(0.8, 0.8, 0.8), 0.3};
  RYT::Metal metalRight = {RYT::Color(0.8, 0.6, 0.2), 1.0};

  RYT::Dielectric material_bubble = {1.00 / 1.50};
  RYT::Dielectric dielectricLeft = {1.50};

  RYT::PushHittable(&world,
                    RYT::Sphere(RYT::Vec3(0, 0, -1.2), 0.5, materialCenter));
  RYT::PushHittable(&world,
                    RYT::Sphere(RYT::Vec3(0, -100.5, -1), 100, materialGround));
  RYT::PushHittable(&world,
                    RYT::Sphere(RYT::Vec3(-1, 0, -1), 0.5, dielectricLeft));
  RYT::PushHittable(&world,
                    RYT::Sphere(RYT::Vec3(-1, 0, -1), 0.4, material_bubble));
  RYT::PushHittable(&world,
                    RYT::Sphere(RYT::Vec3(1, 0, -1.0), 0.5, metalRight));

  RYT::Camera cam;

  cam.SetLookFrom(RYT::Vec3(-2, 2, 1));
  cam.SetLookAt(RYT::Vec3(0, 0, -1));
  cam.SetFov(20);
  cam.SetSamplesPerPixels(10);
  cam.SetDefocusAngle(0);
  cam.SetFocusDistance(10);

  cam.Render(&world);
  RYT::DestroyRaytracingContext(&world);
}

void RenderFovCheck() {
  RYT::RaytracingContext world;
  RYT::InitializeRaytracingContext(&world, 16);

  RYT::Lambertian materialLeft = {RYT::Color(0, 0, 1)};
  RYT::Lambertian materialRight = {RYT::Color(0, 1, 0)};

  double radians = std::cos(RYT::pi / 4);

  RYT::PushHittable(
      &world, RYT::Sphere(RYT::Vec3(-radians, 0, -1), radians, materialLeft));
  RYT::PushHittable(
      &world, RYT::Sphere(RYT::Vec3(radians, 0, -1), radians, materialRight));

  RYT::Camera cam;
  cam.Render(&world);

  RYT::DestroyRaytracingContext(&world);
}

void RenderSample() {
  RYT::RaytracingContext world;
  RYT::InitializeRaytracingContext(&world, 16);

  RYT::Lambertian red = {RYT::Color(0.75, 0.1, 0.1)};
  RYT::Lambertian green = {RYT::Color(0.1, 0.75, 0.1)};
  RYT::Lambertian yellow = {RYT::Color(0.75, 0.75, 0.05)};
  RYT::Lambertian blue = {RYT::Color(0.1, 0.1, 0.75)};
  RYT::Metal mirror = {RYT::Color(1, 1, 1), 0.15};

  RYT::PushHittable(&world, RYT::Sphere(RYT::Vec3(0, 0.5, -2),
                                        RYT::Vec3(0, -0.25, -2), 1, red));
  RYT::PushHittable(&world, RYT::Sphere(RYT::Vec3(0, -200.5, -2), 200, mirror));
  RYT::PushHittable(&world, RYT::Sphere(RYT::Vec3(-3, 0.5, -2), 1, yellow));
  RYT::PushHittable(&world, RYT::Sphere(RYT::Vec3(-1.5, 0.5, -3.5), 1, blue));

  world.bvhRootIndex = RYT::ConstructBVHTree(&world, 0, world.hittableSize);

  RYT::Camera cam;
  cam.SetLookFrom(RYT::Vec3(2.5, 7.5, 5));
  cam.SetLookAt(RYT::Vec3(-1.5, 0.5, -2));
  cam.SetFov(40);
  cam.SetDefocusAngle(0);
  cam.SetFocusDistance(10.5);
  cam.SetSamplesPerPixels(100);

  cam.Render(&world);

  RYT::DestroyRaytracingContext(&world);
}

void RenderHeavy() {
  RYT::RaytracingContext world;
  RYT::InitializeRaytracingContext(&world, 120);

  RYT::Lambertian groundMaterial = {RYT::Color(0.5, 0.5, 0.5)};
  RYT::PushHittable(&world,
                    RYT::Sphere(RYT::Vec3(0, -1000, 0), 1000, groundMaterial));

  for (int i = 0; i < 100; i++) {
    RYT::Vec3 center(i * RYT::RandomDouble(), 0, i * RYT::RandomDouble());
    RYT::Lambertian mat = {RYT::Color(RYT::RandomDouble(), RYT::RandomDouble(),
                                      RYT::RandomDouble())};
    RYT::PushHittable(&world, RYT::Sphere(center, 5, mat));
  }
  // Optimise World By Constructing A BVH Tree
  RYT::OptimizeRaytracingContext(&world);

  RYT::Camera cam;
  cam.SetSamplesPerPixels(10);
  cam.SetMaxDepth(10);
  cam.SetFov(20);
  cam.SetLookFrom(RYT::Vec3(50, 50, 50));
  cam.SetLookAt(RYT::Vec3(0, 0, 0));

  cam.Render(&world);
}
int main(int argc, char *argv[]) {

  auto start = std::chrono::high_resolution_clock::now();
  RenderHeavy();

  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);

  std::clog << "[ LOG ] Rendering Time : " << duration.count() << " seconds"
            << std::endl;
}
