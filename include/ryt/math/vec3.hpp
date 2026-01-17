#ifndef VEC3_H
#define VEC3_H

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
}

#endif
