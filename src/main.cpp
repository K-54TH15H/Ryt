
// math
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

    ryt::PushHittable(&world, ryt::Sphere(ryt::vec3(0, 0, -1), 0.5));
    ryt::PushHittable(&world, ryt::Sphere(ryt::vec3(0, -100.5, -1), 100));

    ryt::Camera cam;

    cam.Render(&world);

    ryt::DestroyRaytracingContext(&world);

    return 0;
}
