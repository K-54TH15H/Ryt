#include "ryt/core/hittable.hpp"
#include "ryt/core/rtcontext.hpp"
#include "ryt/graphics/color.hpp"
#include "ryt/graphics/material.hpp"
#include "ryt/graphics/quad.hpp"
#include "ryt/math/vec3.hpp"
#include "ryt/utils/camera.hpp"
#include <chrono>
// #include <cmath>
#include <ryt/rtcore.hpp>

void CornellBox() {
  RYT::RaytracingContext world;
  RYT::InitializeRaytracingContext(&world, 10, 10, 10, 10);

  int redTexId =
      RYT::PushTexture(&world, RYT::SolidTexture(RYT::Color(0.65, 0.05, 0.05)));
  int whiteTexId =
      RYT::PushTexture(&world, RYT::SolidTexture(RYT::Color(0.73, 0.73, 0.73)));
  int greenTexId =
      RYT::PushTexture(&world, RYT::SolidTexture(RYT::Color(0.12, 0.45, 0.15)));
  int lightTexId =
      RYT::PushTexture(&world, RYT::SolidTexture(RYT::Color(15, 15, 15)));

  RYT::Lambertian redMat = {redTexId};
  RYT::Lambertian whiteMat = {whiteTexId};
  RYT::Lambertian greenMat = {greenTexId};
  RYT::Emmisive lightMat = {lightTexId};

  int redMatId = RYT::PushMaterial(&world, redMat);
  int whiteMatId = RYT::PushMaterial(&world, whiteMat);
  int greenMatId = RYT::PushMaterial(&world, greenMat);
  int lightMatId = RYT::PushMaterial(&world, lightMat);

  RYT::Metal glassMat = {RYT::Color(1.0, 1.0, 1.0), 0.0};

  int glassMatId = RYT::PushMaterial(&world, glassMat);

  RYT::PushHittable(&world,
                    RYT::Quad(RYT::Vec3(555, 0, 0), RYT::Vec3(0, 555, 0),
                              RYT::Vec3(0, 0, 555), greenMatId));
  RYT::PushHittable(&world, RYT::Quad(RYT::Vec3(0, 0, 0), RYT::Vec3(0, 555, 0),
                                      RYT::Vec3(0, 0, 555), redMatId));
  RYT::PushHittable(&world,
                    RYT::Quad(RYT::Vec3(343, 554, 332), RYT::Vec3(-130, 0, 0),
                              RYT::Vec3(0, 0, -105), lightMatId));
  RYT::PushHittable(&world, RYT::Quad(RYT::Vec3(0, 0, 0), RYT::Vec3(555, 0, 0),
                                      RYT::Vec3(0, 0, 555), whiteMatId));
  RYT::PushHittable(&world,
                    RYT::Quad(RYT::Vec3(555, 555, 555), RYT::Vec3(-555, 0, 0),
                              RYT::Vec3(0, 0, -555), whiteMatId));
  RYT::PushHittable(&world,
                    RYT::Quad(RYT::Vec3(0, 0, 555), RYT::Vec3(555, 0, 0),
                              RYT::Vec3(0, 555, 0), whiteMatId));

  RYT::PushHittable(&world,
                    RYT::Sphere(RYT::Vec3(150, 100, 140), 100, glassMatId));
  RYT::PushHittable(&world,
                    RYT::Sphere(RYT::Vec3(375, 125, 380), 125, glassMatId));

  RYT::OptimizeRaytracingContext(&world);

  RYT::Camera cam;

  cam.SetSamplesPerPixels(500);
  cam.SetMaxDepth(10);
  cam.SetBackGroundColor(RYT::Color(1, 1, 1));
  cam.SetFov(40);
  cam.SetLookFrom(RYT::Vec3(278, 278, -800));
  cam.SetLookAt(RYT::Vec3(278, 278, 0));

  cam.SetDefocusAngle(0);
  cam.Render(&world);

  RYT::DestroyRaytracingContext(&world);
}

int main(int argc, char *argv[]) {

  auto start = std::chrono::high_resolution_clock::now();
  CornellBox();

  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);

  std::clog << "[ LOG ] Rendering Time : " << duration.count() << " seconds"
            << std::endl;
}
