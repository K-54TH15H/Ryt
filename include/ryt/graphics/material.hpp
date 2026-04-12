#ifndef MATERIAL_HPP
#define MATERIAL_HPP
#include <curand_kernel.h>

#include <ryt/core/hitrecord.hpp>
#include <ryt/graphics/color.hpp>
#include <ryt/graphics/texture.hpp>

#include <ryt/math/ray.hpp>

namespace RYT {

// ********** Material ******** //
enum MaterialType { LAMBERTIAN, METAL, DIELECTRIC, EMMISIVE, NULLMAT };

struct Lambertian {
  int textureId;
};

struct Metal {
  Color albedo;
  double roughness;
};

struct Dielectric {
  double refractionIndex;
};

struct Emmisive {
  int textureId;
  double strength;
};

class Material {
private:
  MaterialType type;

  union MemberData {
    Lambertian lambertian;
    Metal metal;
    Dielectric dielectric;
    Emmisive emmisive;

    MemberData() {};
    ~MemberData() {};
  } data;

  __host__ __device__ bool ScatterLambertian(const Ray &rIn,
                                             const HitRecord &rec,
                                             Color &attenuation, Ray &scattered,
                                             curandState *state) const;
  __host__ __device__ bool ScatterMetal(const Ray &rIn, const HitRecord &rec,
                                        Color &attenuation, Ray &scattered,
                                        curandState *state) const;

  __host__ __device__ bool ScatterDielectric(const Ray &rIn,
                                             const HitRecord &rec,
                                             Color &attenuation, Ray &scattered,
                                             curandState *state) const;

public:
  // Constructors
  Material();
  Material(const Lambertian lambertian);
  Material(const Metal metal);
  Material(const Dielectric dielectric);
  Material(const Emmisive emmisive);

  ~Material();

  __host__ __device__ bool Scatter(const Ray &rIn, const HitRecord &rec,
                                   Color &attenuation, Ray &scattered,
                                   curandState *state) const;

  __host__ __device__ Color Emit(HitRecord &rec) const;
};

} // namespace RYT
#endif
