#include <ryt/rtcore.hpp>


void RenderDesertScene()
{
    RYT::RaytracingContext world;
    RYT::InitializeRaytracingContext(&world, 16);

    RYT::Metal materialGround = { RYT::Color(0.12, 0.26, 0.70), 0.25};
    RYT::Lambertian materialMountain = { RYT::Color(0.65, 0.18, 0.15)};
    
    RYT::PushHittable(&world, RYT::Sphere(RYT::Vec3(0, -200.5, -1), 200, materialGround));
    RYT::PushHittable(&world, RYT::Sphere(RYT::Vec3(-1, -20, -100), 60, materialMountain));

    RYT::Camera cam;

    cam.Render(&world);

    RYT::DestroyRaytracingContext(&world);
}

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

    cam.Render(&world);

    RYT::DestroyRaytracingContext(&world);
}

int main()
{
    RenderDefaultScene();

    return 0;
}
