#include <ryt/rtcore.hpp>
#include <cmath>

void RenderDefaultScene()
{
    RYT::RaytracingContext world;
    RYT::InitializeRaytracingContext(&world, 16);
    
    RYT::Lambertian materialGround = {RYT::Color(0.8, 0.8, 0.0)};
    RYT::Lambertian materialCenter = {RYT::Color(0.2, 0.1, 0.7)};
    RYT::Metal metalLeft = {RYT::Color(0.8, 0.8, 0.8), 0.3};
    RYT::Metal metalRight = {RYT::Color(0.8, 0.6, 0.2), 1.0};
    
    RYT::Dielectric material_bubble = { 1.00 / 1.50 };
    RYT::Dielectric dielectricLeft = {1.50};
    
    RYT::PushHittable(&world, RYT::Sphere(RYT::Vec3(0, 0, -1.2), 0.5, materialCenter));
    RYT::PushHittable(&world, RYT::Sphere(RYT::Vec3(0, -100.5, -1), 100, materialGround));
    RYT::PushHittable(&world, RYT::Sphere(RYT::Vec3(-1, 0, -1), 0.5, dielectricLeft));
    RYT::PushHittable(&world, RYT::Sphere(RYT::Vec3(-1, 0, -1), 0.4, material_bubble));
    RYT::PushHittable(&world, RYT::Sphere(RYT::Vec3(1, 0, -1.0), 0.5, metalRight));

    RYT::Camera cam;
    
    cam.SetLookFrom(RYT::Vec3(-2, 2, 1));
    cam.SetLookAt(RYT::Vec3(0, 0, -1));
    cam.SetFov(20);
    cam.SetSamplesPerPixels(500);
    cam.SetDefocusAngle(10);
    cam.SetFocusDistance(3.5);

    cam.Render(&world);
    RYT::DestroyRaytracingContext(&world);
}

void RenderFovCheck()
{
    RYT::RaytracingContext world;
    RYT::InitializeRaytracingContext(&world, 16);

    RYT::Lambertian materialLeft = { RYT::Color(0, 0, 1)};
    RYT::Lambertian materialRight = { RYT::Color(0, 1, 0)};
    
    double radians = std::cos(RYT::pi / 4);

    RYT::PushHittable(&world, RYT::Sphere(RYT::Vec3(-radians, 0, -1), radians, materialLeft)); 
    RYT::PushHittable(&world, RYT::Sphere(RYT::Vec3(radians, 0, -1), radians, materialRight)); 

    RYT::Camera cam;
    cam.Render(&world);

    RYT::DestroyRaytracingContext(&world);
}

int main()
{
    RenderDefaultScene();

    return 0;
}
