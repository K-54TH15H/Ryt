#include <ryt/rtcore.hpp>
#include <cmath>

namespace RYT
{
    void Camera::Render(const RaytracingContext* world)
    {
	Initialize();

	std::cout << "P3" << std::endl << imgW << ' ' << imgH << std::endl << 255 << std::endl;

	for(int i = 0; i < imgH; i++)
	{
	    // clear up line
	    std::clog << '\r' << std::string(25, ' ') << '\r';
	    // write progress
	    std::clog << "Progress : " << ((((double)i)/(imgH-1)) * 100) << '%';

	    for(int j = 0; j < imgW; j++)
	    {
		Color pixelColor(0, 0, 0);

		for(int sample = 0; sample < samplesPerPixels; sample++)
		{
		    Ray r = GetRay(j, i);
		    pixelColor += RayColor(r, maxDepth, world);
		}
		WriteColor(std::cout, pixelSamplesScale * pixelColor);
	    }
	}
	std::clog << std::endl << "Render Complete" << std::endl;
    }

    void Camera::Initialize()
    {
	aspectRatio = 16.0 / 9.0;
	imgW = 1440;

	// calculate img_h and clamp to 1
	imgH = int(imgW / aspectRatio);
	imgH = (imgH < 1) ? 1 : imgH;
	
	// Set up Look From and Look at by default on Initialisation
	lookFrom = Vec3(-2, 2, 1);
	lookAt = Vec3(0, 0, -1);
	center = lookFrom; 

	samplesPerPixels = 100; // anti-aliasing on by default
	pixelSamplesScale = 1.0 / samplesPerPixels;
	maxDepth = 10;
	
	vFov = 20; // Default set to 90^
	double focalLength = (lookFrom - lookAt).Length();
	double theta = DegreesToRadians(vFov);
	double h = std::tan(theta / 2);

	double viewportHeight = 2.0 * h * focalLength;
	double viewportWidth = viewportHeight * (double(imgW) / imgH);
	
	// Calculate Relative Frame Basis
	w = UnitVector(lookFrom - lookAt);
	u = UnitVector(Cross(Vec3(0, 1, 0), w));
	v = UnitVector(Cross(w, u));

	// Calculate vecs accross horizontal and vertical viewport edges
	Vec3 viewportU = viewportWidth * u;
	Vec3 viewportV = -viewportHeight * v;

	// Calculate Offset vecs
	pixelDeltaU = viewportU / imgW;
	pixelDeltaV = viewportV / imgH;

	Vec3 viewportUpperLeft = center - (focalLength * w) - (viewportU/2) - (viewportV / 2);
	pixel00Loc = viewportUpperLeft + 0.5 * ( pixelDeltaU + pixelDeltaV );
    }

    Vec3 Camera::SampleSquare() const
    {
	return Vec3(RandomDouble() - 0.5, RandomDouble() - 0.5, 0);
    }

    // Constructs a camera Ray from origin to a randomly sampled pt i, j
    Ray Camera::GetRay(int i, int j) const
    {
	Vec3 offset = SampleSquare();
	Vec3 pixelSample = pixel00Loc 
	    + ((i + offset.x) * pixelDeltaU)
	    + ((j + offset.y) * pixelDeltaV);

	Vec3 rayOrigin = center;
	Vec3 rayDirection = pixelSample - rayOrigin;

	return Ray(rayOrigin, rayDirection);
    }

    Color Camera::RayColor(const Ray& r, int depth, const RaytracingContext* world) const
    {
	Ray currentRay = r;

	Color accumulatedLight(0, 0, 0);
	Color throughput(1.0, 1.0, 1.0);

	for(int i = 0; i < maxDepth; i++)
	{
	    HitRecord rec;

	    if(HitWorld(world, currentRay, Interval(0.001, infinity), rec))
	    {
		Ray scattered;
		Color attenuation;

		if(rec.mat->Scatter(currentRay, rec, attenuation, scattered))
		{
		    throughput = throughput * attenuation;
		    currentRay = scattered;
		}
		else return Color(0, 0, 0);

	    }
	    else
	    {
		Vec3 unitDirection = UnitVector(currentRay.Direction());
		double a = 0.5 * (unitDirection.y + 1.0);

		Color skyColor = (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);

		accumulatedLight = throughput * skyColor;

		return accumulatedLight;
	    }
	}

	//Ray is absorbed(trapped) [returns black]
	return Color(0, 0, 0); 	    
    }

}
