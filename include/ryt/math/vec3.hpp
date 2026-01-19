#ifndef VEC3_H
#define VEC3_H

#include <ryt/math/random.hpp>

#include <cmath>
#include <iostream>

namespace ryt
{
    class Vec3
    {
	public:
	    // data
	    double x, y, z;
	    
	    // constructors
	    Vec3() : x(0), y(0), z(0) {}
	    Vec3(double x, double y, double z) : x(x), y(y), z(z) {}

	    // operator overloadings
	    Vec3 operator-() const
	    {
		return Vec3(-x, -y, -z);
	    }

	    Vec3& operator+=(const Vec3& v)
	    {
		x += v.x;
		y += v.y;
		z += v.z;
		
		return *this;
	    }

	    Vec3& operator*=(double t)
	    {
		x *= t;
		y *= t;
		z *= t;

		return *this;
	    }

	    Vec3& operator/=(double t)
	    {
		return *this *= 1/t;
	    }
	    
	    // length functions
	    double LengthSquared() const
	    {
		return ( (x*x) + (y*y) + (z*z) );
	    }

	    double Length() const { return std::sqrt(LengthSquared()); }

	    bool NearZero() const
	    {
		auto co = 1e-8; // cuttoff
		return (std::fabs(x) < co) && (std::fabs(y) < co) && (std::fabs(z) < co);
	    }

	    static Vec3 Random()
	    {
		return Vec3(RandomDouble(), RandomDouble(), RandomDouble());
	    }

	    static Vec3 Random(double min, double max)
	    {
		return Vec3(RandomDouble(min, max), RandomDouble(min, max), RandomDouble(min, max));
	    }
    };

    // vector utility functions

    inline std::ostream& operator<<(std::ostream& os, const Vec3& v)
    {
	return os << v.x << ' ' << v.y  << ' ' << v.z;
    }

    inline Vec3 operator+(const Vec3& u, const Vec3& v)
    {
	return Vec3((u.x + v.x), (u.y + v.y), (u.z + v.z));
    }

    inline Vec3 operator-(const Vec3& u, const Vec3& v)
    {
	return Vec3((u.x - v.x), (u.y - v.y), (u.z - v.z));
    }

    inline Vec3 operator*(double t, const Vec3& v)
    {
	return Vec3(t * v.x, t * v.y, t * v.z);
    }

    inline Vec3 operator*(const Vec3& u, const Vec3& v)
    {
	return Vec3(u.x * v.x, u.y * v.y, u.z * v.z);
    }

    inline Vec3 operator/(const Vec3& v, double t)
    {
	return (1/t) * v;
    }

    inline double Dot(const Vec3& u, const Vec3& v)
    {
	return (u.x * v.x) + (u.y * v.y) + (u.z * v.z);
    }

    inline Vec3 Cross(const Vec3& u, const Vec3& v)
    {
	return Vec3(u.y * v.z - u.z * v.y,
		    u.z * v.x - u.x * v.z,
		    u.x * v.y - u.y * v.x
		    );
    }

    inline Vec3 UnitVector(const Vec3& v)
    {
	return v/v.Length();
    }

    inline Vec3 RandomUnitVector()
    {
	while(true)
	{
	    Vec3 p = Vec3::Random(-1, 1);
	    double lenSq = p.LengthSquared();

	    if(1e-160 < lenSq && lenSq <= 1) return (p / sqrt(lenSq));
	}
    }

    inline Vec3 RandomOnHemisphere(const Vec3& normal)
    {
	Vec3 onUnitSphere = RandomUnitVector();

	if(Dot(onUnitSphere, normal) > 0.0) return onUnitSphere;
	else return -onUnitSphere;
    }

    inline Vec3 Reflect(const Vec3& v, const Vec3& n)
    {
	return v - (2 * Dot(v,n) * n);
    }
}

#endif
