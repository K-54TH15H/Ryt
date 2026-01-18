#ifndef VEC3_H
#define VEC3_H

#include <ryt/math/random.hpp>

#include <cmath>
#include <iostream>

namespace ryt
{
    class vec3
    {
	public:
	    // data
	    double x, y, z;
	    
	    // constructors
	    vec3() : x(0), y(0), z(0) {}
	    vec3(double x, double y, double z) : x(x), y(y), z(z) {}

	    // operator overloadings
	    vec3 operator-() const
	    {
		return vec3(-x, -y, -z);
	    }

	    vec3& operator+=(const vec3& v)
	    {
		x += v.x;
		y += v.y;
		z += v.z;
		
		return *this;
	    }

	    vec3& operator*=(double t)
	    {
		x *= t;
		y *= t;
		z *= t;

		return *this;
	    }

	    vec3& operator/=(double t)
	    {
		return *this *= 1/t;
	    }
	    
	    // length functions
	    double length_squared() const
	    {
		return ( (x*x) + (y*y) + (z*z) );
	    }

	    double length() const { return std::sqrt(length_squared()); }

	    static vec3 random()
	    {
		return vec3(random_double(), random_double(), random_double());
	    }

	    static vec3 random(double min, double max)
	    {
		return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
	    }
    };

    // vector utility functions

    inline std::ostream& operator<<(std::ostream& os, const vec3& v)
    {
	return os << v.x << ' ' << v.y  << ' ' << v.z;
    }

    inline vec3 operator+(const vec3& u, const vec3& v)
    {
	return vec3((u.x + v.x), (u.y + v.y), (u.z + v.z));
    }

    inline vec3 operator-(const vec3& u, const vec3& v)
    {
	return vec3((u.x - v.x), (u.y - v.y), (u.z - v.z));
    }

    inline vec3 operator*(double t, const vec3& v)
    {
	return vec3(t * v.x, t * v.y, t * v.z);
    }

    inline vec3 operator*(const vec3& u, const vec3& v)
    {
	return vec3(u.x * v.x, u.y * v.y, u.z * v.z);
    }

    inline vec3 operator/(const vec3& v, double t)
    {
	return (1/t) * v;
    }

    inline double dot(const vec3& u, const vec3& v)
    {
	return (u.x * v.x) + (u.y * v.y) + (u.z * v.z);
    }

    inline vec3 cross(const vec3& u, const vec3& v)
    {
	return vec3(u.y * v.z - u.z * v.y,
		    u.z * v.x - u.x * v.z,
		    u.x * v.y - u.y * v.x
		    );
    }

    inline vec3 unit_vector(const vec3& v)
    {
	return v/v.length();
    }

    inline vec3 random_unit_vector()
    {
	while(true)
	{
	    vec3 p = vec3::random(-1, 1);
	    double len_sq = p.length_squared();

	    if(1e-160 < len_sq && len_sq <= 1) return (p / sqrt(len_sq));
	}
    }

    inline vec3 random_on_hemisphere(const vec3& normal)
    {
	vec3 on_unit_sphere = random_unit_vector();

	if(dot(on_unit_sphere, normal) > 0.0) return on_unit_sphere;
	else return -on_unit_sphere;
    }
}

#endif
