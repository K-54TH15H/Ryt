#include <ryt/rtcore.hpp>

namespace RYT
{
    bool Material::ScatterLambertian(const Ray& rIn, const HitRecord& rec, Color& attenuation, Ray& scattered) const
    {
	Vec3 scatterDirection = rec.normal + RandomUnitVector();

	if(scatterDirection.NearZero()) scatterDirection = rec.normal;

	scattered = Ray(rec.p, scatterDirection);
	attenuation = data.lambertian.albedo;

	return true;
    }

    bool Material::ScatterMetal(const Ray& rIn, const HitRecord& rec, Color& attenuation, Ray& scattered) const
    {
	Vec3 reflected = Reflect(rIn.Direction(), rec.normal);
	reflected = (UnitVector(reflected)) + (data.metal.roughness * RandomUnitVector());

	scattered = Ray(rec.p, reflected);
	attenuation = data.metal.albedo;

	return (Dot(scattered.Direction(), rec.normal) > 0);

    }

    Material::Material(const Lambertian lambertian) : type(LAMBERTIAN) 
    {
	data.lambertian = lambertian;
    }

    Material::Material(const Metal metal) : type(METAL) 
    {
	data.metal = metal;
    }

    Material::~Material()
    {
	switch(type)
	{
	    case LAMBERTIAN:
		(data.lambertian).~Lambertian();
		break;

	    case METAL:
		(data.metal).~Metal();
		break;
	}
    }

    bool Material::Scatter(const Ray& rIn, const HitRecord& rec, Color& attenuation, Ray& scattered) const 
    {
	switch(type)
	{
	    case LAMBERTIAN:
		return this->ScatterLambertian(rIn, rec, attenuation, scattered);

	    case METAL:
		return this->ScatterMetal(rIn, rec, attenuation, scattered);

	    default:
		return false;
	}
    }
}
