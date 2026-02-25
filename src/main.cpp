#include "ryt/core/rtcontext.hpp"
#include "ryt/graphics/color.hpp"
#include "ryt/graphics/texture.hpp"
#include <chrono>
// #include <cmath>
#include <ryt/rtcore.hpp>

void RandomScene() {
  std::srand(time(nullptr));

  RYT::RaytracingContext world;
  RYT::InitializeRaytracingContext(&world, 100, 103);

  RYT::Texture blue(RYT::Color(0.2, 0.5, 0.8));
  RYT::Texture red(RYT::Color(0.1, 0.1, 0.1));

  int blueId = RYT::PushTexture(&world, blue);
  int redId = RYT::PushTexture(&world, red);

  RYT::CheckerTexture checker(5, blueId, redId);
  int checkerId = RYT::PushTexture(&world, checker);

  RYT::Lambertian groundMaterial = {checkerId};
  RYT::PushHittable(
      &world, RYT::Sphere(RYT::Vec3(0, -100000, 0), 100000, groundMaterial));

  RYT::Metal glassMaterial = {RYT::Color(1, 1, 1), 0};
  RYT::PushHittable(&world,
                    RYT::Sphere(RYT::Vec3(0, 15, 0), 15, glassMaterial));

  for (int i = 0; i < 100; i++) {
    int matDecider = RYT::RandomInt(0, 10);
    RYT::Color randomColor(RYT::RandomDouble(), RYT::RandomDouble(),
                           RYT::RandomDouble());

    RYT::Lambertian lam = {RYT::PushTexture(&world, randomColor)};
    RYT::Metal met = {randomColor, RYT::RandomDouble()};

    RYT::Vec3 pos(-200 + RYT::RandomInt(0, 620), 5,
                  250 - RYT::RandomInt(0, 400));

    if (matDecider > 5) {
      RYT::PushHittable(&world, RYT::Sphere(pos, 5, lam));
    } else {
      RYT::PushHittable(&world, RYT::Sphere(pos, 5, met));
    }
  }

  RYT::OptimizeRaytracingContext(&world);

  RYT::Camera cam;
  cam.SetSamplesPerPixels(10);
  cam.SetMaxDepth(10);
  cam.SetFov(20);
  cam.SetLookFrom(RYT::Vec3(-50, 35, -40));
  cam.SetLookAt(RYT::Vec3(0, 0, 0));
  cam.SetFov(90);

  cam.Render(&world);
}

int main(int argc, char *argv[]) {

  auto start = std::chrono::high_resolution_clock::now();
  RandomScene();

  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);

  std::clog << "[ LOG ] Rendering Time : " << duration.count() << " seconds"
            << std::endl;
}
