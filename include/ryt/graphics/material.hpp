#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <ryt/core/hitrecord.hpp>
#include <ryt/graphics/color.hpp>
#include <ryt/math/ray.hpp>

namespace RYT {

// ********** Material ******** //
enum MaterialType { LAMBERTIAN, METAL, DIELECTRIC };

struct Lambertian {
  Color albedo;
};

struct Metal {
  Color albedo;
  double roughness;
};

struct Dielectric {
  double refractionIndex;
};

class Material {
private:
  MaterialType type;

  union MemberData {
    Lambertian lambertian;
    Metal metal;
    Dielectric dielectric;

    MemberData() {};
    ~MemberData() {};
  } data;

  bool ScatterLambertian(const Ray &rIn, const HitRecord &rec,
                         Color &attenuation, Ray &scattered) const;
  bool ScatterMetal(const Ray &rIn, const HitRecord &rec, Color &attenuation,
                    Ray &scattered) const;
  bool ScatterDielectric(const Ray &rIn, const HitRecord &rec,
                         Color &attenuation, Ray &scattered) const;

public:
  // Constructors
  Material(const Lambertian lambertian);
  Material(const Metal metal);
  Material(const Dielectric dielectric);

  ~Material();

  bool Scatter(const Ray &rIn, const HitRecord &rec, Color &attenuation,
               Ray &scattered) const;
};

} // namespace RYT
#endif
