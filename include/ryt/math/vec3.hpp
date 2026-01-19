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
	    double length_squared() const
	    {
		return ( (x*x) + (y*y) + (z*z) );
	    }

	    double length() const { return std::sqrt(length_squared()); }

	    bool near_zero() const
	    {
		auto co = 1e-8; // cuttoff
		return (std::fabs(x) < co) && (std::fabs(y) < co) && (std::fabs(z) < co);
	    }

	    static Vec3 random()
	    {
		return Vec3(RandomDouble(), RandomDouble(), RandomDouble());
	    }

	    static Vec3 random(double min, double max)
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

    inline double dot(const Vec3& u, const Vec3& v)
    {
	return (u.x * v.x) + (u.y * v.y) + (u.z * v.z);
    }

    inline Vec3 cross(const Vec3& u, const Vec3& v)
    {
	return Vec3(u.y * v.z - u.z * v.y,
		    u.z * v.x - u.x * v.z,
		    u.x * v.y - u.y * v.x
		    );
    }

    inline Vec3 unit_vector(const Vec3& v)
    {
	return v/v.length();
    }

    inline Vec3 random_unit_vector()
    {
	while(true)
	{
	    Vec3 p = Vec3::random(-1, 1);
	    double len_sq = p.length_squared();

	    if(1e-160 < len_sq && len_sq <= 1) return (p / sqrt(len_sq));
	}
    }

    inline Vec3 random_on_hemisphere(const Vec3& normal)
    {
	Vec3 on_unit_sphere = random_unit_vector();

	if(dot(on_unit_sphere, normal) > 0.0) return on_unit_sphere;
	else return -on_unit_sphere;
    }

    inline Vec3 reflect(const Vec3& v, const Vec3& n)
    {
	return v - (2 * dot(v,n) * n);
    }
}

#endif
