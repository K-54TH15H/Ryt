
// math
#include "ryt/graphics/material/mcore.hpp"
#include <ryt/math/vec3.hpp>
#include <ryt/math/ray.hpp>

// graphics
#include <ryt/graphics/color.hpp>
#include <ryt/graphics/hittable.hpp>
#include <ryt/graphics/hit_record.hpp>
#include <ryt/graphics/sphere.hpp>
#include <ryt/graphics/rtcontext.hpp>

// utils
#include <ryt/utils/camera.hpp>

int main()
{
    ryt::RaytracingContext world;
    ryt::InitializeRaytracingContext(&world, 16);
    
    ryt::Lambertian material_ground(ryt::color(0.8, 0.8, 0.0));
    ryt::Lambertian material_center(ryt::color(0.7, 0.1, 0.2));
    ryt::Metal metal_left(ryt::color(0.8, 0.8, 0.8));
    ryt::Metal metal_right(ryt::color(0.8, 0.6, 0.2));

    
    ryt::PushHittable(&world, ryt::Sphere(ryt::vec3(0, 0, -1.2), 0.5, material_center));
    ryt::PushHittable(&world, ryt::Sphere(ryt::vec3(0, -100.5, -1), 100, material_ground));
    ryt::PushHittable(&world, ryt::Sphere(ryt::vec3(-1, 0, -1), 0.5, metal_left));
    ryt::PushHittable(&world, ryt::Sphere(ryt::vec3(1, 0, -1.0), 0.5, metal_right));

    ryt::Camera cam;

    cam.Render(&world);

    ryt::DestroyRaytracingContext(&world);

    return 0;
}
