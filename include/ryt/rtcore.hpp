#ifndef RTCORE_HPP
#define RTCORE_HPP

// Dependencies
#include <iostream>
#include <limits>

namespace RYT
{
    // ********** VEC3 ********** //
    class Vec3
    {
	public:
	    // data
	    double x, y, z;
	    
	    // constructors
	    Vec3();
	    Vec3(double x, double y, double z);

	    // operator overloadings
	    Vec3 operator-() const;
	    
	    Vec3& operator+=(const Vec3& v);
	    Vec3& operator*=(double t);
	    Vec3& operator/=(double t);
	    	    
	    // length functions
	    double LengthSquared() const;
	    double Length() const;

	    bool NearZero() const;

	    static Vec3 Random();

	    static Vec3 Random(double min, double max);
	    
    };

    // vector utility functions
    std::ostream& operator<<(std::ostream& os, const Vec3& v);
    Vec3 operator+(const Vec3& u, const Vec3& v);
    Vec3 operator-(const Vec3& u, const Vec3& v);
    Vec3 operator*(double t, const Vec3& v);
    Vec3 operator*(const Vec3& u, const Vec3& v);
    Vec3 operator/(const Vec3& v, double t);
    double Dot(const Vec3& u, const Vec3& v);
    Vec3 Cross(const Vec3& u, const Vec3& v);
    Vec3 UnitVector(const Vec3& v);
    Vec3 RandomUnitVector();
    Vec3 RandomOnHemisphere(const Vec3& normal);
    Vec3 Reflect(const Vec3& v, const Vec3& n);
    Vec3 Refract(const Vec3& uv, const Vec3& n, double etai_over_etat);

    // ********** RAY ********** //
    class Ray
    {
	private:
	    Vec3 orig;
	    Vec3 dir;
	public:

	    // constructors
	    Ray();
	    Ray(const Vec3& origin, const Vec3& direction); 
	    
	    // getters
	    const Vec3& Origin() const;
	    const Vec3& Direction() const;
	    Vec3 At(double t) const;
    };
    
    // ********** Common ********** //
    double RandomDouble();
    double RandomDouble(double min, double max);
    double DegreesToRadians(double degrees);

    // ********** Interval ********** //
    // Interval constants
    inline const double infinity = std::numeric_limits<double>::infinity();
    inline const double pi = 3.1415926535897932385;
    
    
    class Interval
    {
	public:
	    double min, max;
	    
	    // Default interval [inf, -inf] ( empty )
	    Interval();	    
	    // Range based constructor
	    Interval(double min, double max);

	    double Size() const; 
	    bool Contains(double x) const;
	    bool Surrounds(double x) const;
	    
	    double Clamp(double x) const;
	    
	    static const Interval empty, universe;
    };

    // Static Constant Intervals
    inline const Interval Interval::empty = Interval(+infinity, -infinity);
    inline const Interval Interval::universe = Interval(-infinity, +infinity);
    

    // ********** Color ********** // 
    using Color = Vec3; // alias for rt::Vec3 as color as an context - might need to modify

    void LinearToGamma(double& linearComponent);
    void WriteColor(std::ostream& os, const Color& pixelColor);

    // ********** HitRecord ********** //
    class Material; // Forward Declarations

    class HitRecord
    {
	public:
	    Vec3 p;
	    Vec3 normal;
	    Material* mat; // This Doesn't Own the Material just points to it.
	    double t;
	    bool frontFace;

	    void SetFaceNormal(const Ray& r, const Vec3& outwardNormal);
    };
    
    // ********** Material ******** //
    enum MaterialType
    {
	LAMBERTIAN,
	METAL,
	DIELECTRIC
    };

    struct Lambertian
    {
	Color albedo;
    };

    struct Metal
    {
	Color albedo;
        double roughness;
    };
    
    struct Dielectric
    {
	double refractionIndex;
    };

    class Material
    {
	private:
	    MaterialType type;

	    union MemberData 
	    {
		Lambertian lambertian;
		Metal metal;
		Dielectric dielectric;

		MemberData() {};
		~MemberData() {};
	    } data;
	    
	    bool ScatterLambertian(const Ray& rIn, const HitRecord& rec, Color& attenuation, Ray& scattered) const;
	    bool ScatterMetal(const Ray& rIn, const HitRecord& rec, Color& attenuation, Ray& scattered) const;
	    bool ScatterDielectric(const Ray& rIn, const HitRecord& rec, Color& attenuation, Ray& scattered) const; 

	public:
	    
	    // Constructors
	    Material(const Lambertian lambertian);
	    Material(const Metal metal);
	    Material(const Dielectric dielectric);

	    ~Material();
	    
	    bool Scatter(const Ray& rIn, const HitRecord& rec, Color& attenuation, Ray& scattered) const ;
    
    };

    // ********** SPHERE ********** //
    class Sphere
    {
	private:
	    Vec3 center;
	    double radius;
	    Material mat;

	public:
	    Sphere(const Vec3& center, double radius, Material mat);

	    bool Hit(const Ray& r, Interval t, HitRecord& rec);
    };
    
    // *********** HITTABLE ********** //
    // Tag for Geometry type
    enum GeometryType
    {
	SPHERE,
	NONE
    };

    class Hittable
    {
	public:
	    GeometryType type;

	    union MemberData
	    {
		Sphere sphere;
	
		// default constructors get destroyed placeholder constructors and destrcutors
		// manually handled via class constructors and destrcutors
		MemberData() {} 
		~MemberData() {}

	    }data;
	    
	    Hittable();
	    Hittable(Sphere s);

	    ~Hittable();
	     
	    bool Hit(const Ray& r, Interval t, HitRecord& rec);
	    
    };
    
    // ********** RAYTRACING-CONTEXT **********
    struct RaytracingContext
    {
	Hittable* hittables;
	size_t hittableSize;
	size_t hittableCapacity;
    };
    
    // Context functions
    void InitializeRaytracingContext(RaytracingContext* context, size_t capacity);
    void DestroyRaytracingContext(RaytracingContext* context);
    Hittable* PushHittable(RaytracingContext* context, Hittable hittable);
    bool HitWorld(const RaytracingContext* context, const Ray& r, Interval t, HitRecord& rec);


    // ********** Camera ********** //
    class Camera
    {
	public:
	    void Render(const RaytracingContext* world);
	    
	private:

	    double aspectRatio; // Ratio of image width to height
	    int imgW; // Rendered image width
	    int imgH; // Rendered image height

	    Vec3 center; // Camera center
	    Vec3 lookFrom; // Look from a point 
	    Vec3 lookAt; // Look at a point
	    
	    Vec3 u, v, w; // Relative camera frame basis

	    Vec3 pixel00Loc; // Location of pixel - [0, 0]
	    Vec3 pixelDeltaU; // Offset for pixel to the right
	    Vec3 pixelDeltaV; // Offset for pixel to the bottom

	    int samplesPerPixels; // Count of random samples per pixels
	    double pixelSamplesScale;
	    int maxDepth; // Maximum no of Ray bounces into scene

	    double vFov; // vertical view angle - FOV

	    void Initialize();
	    Vec3 SampleSquare() const;
	    

	    // Constructs a camera Ray from origin to a randomly sampled pt i, j
	    Ray GetRay(int i, int j) const;
	    Color RayColor(const Ray& r, int depth, const RaytracingContext* world) const;
	    
    };
}

#endif
