#include <cmath>

#include <ryt/graphics/material.hpp>
#include <ryt/math/common.hpp>

namespace RYT {
static double Reflectance(double cosine, double refractionIndex) {
  // Schlick's Approximation
  double r0 = (1 - refractionIndex) / (1 + refractionIndex);
  r0 *= r0;

  return r0 + ((1 - r0) * std::pow((1 - cosine), 5));
}

bool Material::ScatterLambertian(const Ray &rIn, const HitRecord &rec,
                                 Color &attenuation, Ray &scattered) const {
  Vec3 scatterDirection = rec.normal + RandomUnitVector();

  if (scatterDirection.NearZero())
    scatterDirection = rec.normal;

  scattered = Ray(rec.p, scatterDirection, rIn.Time());
  attenuation = data.lambertian.albedo;

  return true;
}

bool Material::ScatterMetal(const Ray &rIn, const HitRecord &rec,
                            Color &attenuation, Ray &scattered) const {
  Vec3 reflected = Reflect(rIn.Direction(), rec.normal);
  reflected =
      (UnitVector(reflected)) + (data.metal.roughness * RandomUnitVector());

  scattered = Ray(rec.p, reflected, rIn.Time());
  attenuation = data.metal.albedo;

  return (Dot(scattered.Direction(), rec.normal) > 0);
}

bool Material::ScatterDielectric(const Ray &rIn, const HitRecord &rec,
                                 Color &attenuation, Ray &scattered) const {
  attenuation = Color(1.0, 1.0, 1.0);
  double ri = rec.frontFace ? (1.0 / data.dielectric.refractionIndex)
                            : data.dielectric.refractionIndex;

  Vec3 unitDirection = UnitVector(rIn.Direction());

  double cosTheta = std::fmin(Dot(-unitDirection, rec.normal), 1.0);
  double sinTheta = std::sqrt(1.0 - (cosTheta * cosTheta));

  bool cannotRefract = (ri * sinTheta > 1);
  Vec3 direction;

  if (cannotRefract || Reflectance(cosTheta, ri) > RandomDouble())
    direction = Reflect(unitDirection, rec.normal);
  else
    direction = Refract(unitDirection, rec.normal, ri);

  scattered = Ray(rec.p, direction, rIn.Time());
  return true;
}

Material::Material(const Lambertian lambertian) : type(LAMBERTIAN) {
  data.lambertian = lambertian;
}

Material::Material(const Metal metal) : type(METAL) { data.metal = metal; }

Material::Material(const Dielectric dielectric) : type(DIELECTRIC) {
  data.dielectric = dielectric;
}

Material::~Material() {
  switch (type) {
  case LAMBERTIAN:
    (data.lambertian).~Lambertian();
    break;

  case METAL:
    (data.metal).~Metal();
    break;

  case DIELECTRIC:
    (data.dielectric).~Dielectric();
    break;
  }
}

bool Material::Scatter(const Ray &rIn, const HitRecord &rec, Color &attenuation,
                       Ray &scattered) const {
  switch (type) {
  case LAMBERTIAN:
    return this->ScatterLambertian(rIn, rec, attenuation, scattered);

  case METAL:
    return this->ScatterMetal(rIn, rec, attenuation, scattered);

  case DIELECTRIC:
    return this->ScatterDielectric(rIn, rec, attenuation, scattered);

  default:
    return false;
  }
}
} // namespace RYT
