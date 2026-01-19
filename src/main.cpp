
// math
#include <ryt/math/vec3.hpp>
#include <ryt/math/ray.hpp>

// graphics
#include <ryt/graphics/color.hpp>
#include <ryt/graphics/hittable.hpp>
#include <ryt/graphics/hit_record.hpp>
#include <ryt/graphics/sphere.hpp>
#include <ryt/graphics/rtcontext.hpp>
#include <ryt/graphics/material.hpp>

// utils
#include <ryt/utils/camera.hpp>

int main()
{
    ryt::RaytracingContext world;
    ryt::InitializeRaytracingContext(&world, 16);
    
    ryt::Lambertian materialGround(ryt::Color(0.8, 0.8, 0.0));
    ryt::Lambertian materialCenter(ryt::Color(0.2, 0.1, 0.7));
    ryt::Metal metalLeft(ryt::Color(0.8, 0.8, 0.8), 0.0);
    ryt::Metal metalRight(ryt::Color(0.8, 0.6, 0.2), 1.0);

    
    ryt::PushHittable(&world, ryt::Sphere(ryt::Vec3(0, 0, -1.2), 0.5, materialCenter));
    ryt::PushHittable(&world, ryt::Sphere(ryt::Vec3(0, -100.5, -1), 100, materialGround));
    ryt::PushHittable(&world, ryt::Sphere(ryt::Vec3(-1, 0, -1), 0.5, metalLeft));
    ryt::PushHittable(&world, ryt::Sphere(ryt::Vec3(1, 0, -1.0), 0.5, metalRight));

    ryt::Camera cam;

    cam.Render(&world);

    ryt::DestroyRaytracingContext(&world);

    return 0;
}
