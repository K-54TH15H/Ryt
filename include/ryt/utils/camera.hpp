#ifndef CAMERA_H
#define CAMERA_H


#include <ryt/math/interval.hpp>
#include <ryt/math/vec3.hpp>

#include <ryt/graphics/material.hpp>
#include <ryt/graphics/color.hpp>
#include <ryt/graphics/hit_record.hpp>
#include <ryt/graphics/rtcontext.hpp>
#include <ryt/graphics/hittable.hpp>

namespace ryt
{
    class Camera
    {
	public:

	    void Render(const RaytracingContext* world)
	    {
		Initialize();

		std::cout << "P3" << std::endl << img_w << ' ' << img_h << std::endl << 255 << std::endl;

		for(int i = 0; i < img_h; i++)
		{
		    // clear up line
		    std::clog << '\r' << std::string(25, ' ') << '\r';
		    // write progress
		    std::clog << "Progress : " << ((((double)i)/(img_h-1)) * 100) << '%';

		    for(int j = 0; j < img_w; j++)
		    {
			color pixel_color(0, 0, 0);

			for(int sample = 0; sample < samples_per_pixels; sample++)
			{
			    Ray r = get_Ray(j, i);
			    pixel_color += Ray_color(r, max_depth, world);
			}
			write_color(std::cout, pixel_samples_scale * pixel_color);
		    }
		}

		std::clog << std::endl << "Render Complete" << std::endl;
	    }

	private:

	    double aspect_ratio; // Ratio of image width to height
	    int img_w; // Rendered image width
	    int img_h; // Rendered image height

	    Vec3 center; // Camera center
	    Vec3 pixel00_loc; // Location of pixel - [0, 0]
	    Vec3 pixel_delta_u; // Offset for pixel to the right
	    Vec3 pixel_delta_v; // Offset for pixel to the bottom

	    int samples_per_pixels; // Count of random samples per pixels
	    double pixel_samples_scale;
	    int max_depth; // Maximum no of Ray bounces into scene

	    void Initialize()
	    {
		aspect_ratio = 16.0 / 9.0;
		img_w = 800;

		// calculate img_h and clamp to 1
		img_h = int(img_w / aspect_ratio);
		img_h = (img_h < 1) ? 1 : img_h;

		center = Vec3(0, 0, 0);
		samples_per_pixels = 10; // anti-aliasing on by default
		pixel_samples_scale = 1.0 / samples_per_pixels;
		max_depth = 10;

		double focal_length = 1.0;
		double viewport_height = 2.0;
		double viewport_width = viewport_height * (double(img_w) / img_h);

		// Calculate vecs accross horizontal and vertical viewport edges
		Vec3 viewport_u = Vec3(viewport_width, 0, 0);
		Vec3 viewport_v = Vec3(0, -viewport_height, 0);

		// Calculate Offset vecs
		pixel_delta_u = viewport_u / img_w;
		pixel_delta_v = viewport_v / img_h;

		Vec3 viewport_upper_left = center - Vec3(0, 0, focal_length) - (viewport_u/2) - (viewport_v / 2);
		pixel00_loc = viewport_upper_left + 0.5 * ( pixel_delta_u + pixel_delta_v );
	    }

	    Vec3 sample_square() const
	    {
		return Vec3(RandomDouble() - 0.5, RandomDouble() - 0.5, 0);
	    }

	    // Constructs a camera Ray from origin to a randomly sampled pt i, j
	    Ray get_Ray(int i, int j) const
	    {
		Vec3 offset = sample_square();
		Vec3 pixel_sample = pixel00_loc 
		    + ((i + offset.x) * pixel_delta_u)
		    + ((j + offset.y) * pixel_delta_v);

		Vec3 Ray_origin = center;
		Vec3 Ray_direction = pixel_sample - Ray_origin;

		return Ray(Ray_origin, Ray_direction);
	    }

	    color Ray_color(const Ray& r, int depth, const RaytracingContext* world) const
	    {
		Ray current_Ray = r;

		color accumulated_light(0, 0, 0);
		color throughput(1.0, 1.0, 1.0);

		for(int i = 0; i < max_depth; i++)
		{
		    Hit_Record rec;

		    if(HitWorld(world, current_Ray, Interval(0.001, infinity), rec))
		    {
			Ray scattered;
			color attenuation;

			if(rec.mat->scatter(current_Ray, rec, attenuation, scattered))
			{
			    throughput = throughput * attenuation;
			    current_Ray = scattered;
			}
			else return color(0, 0, 0);

		    }
		    else
		    {
			Vec3 unit_direction = unit_vector(current_Ray.direction());
			double a = 0.5 * (unit_direction.y + 1.0);

			color sky_color = (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);

			accumulated_light = throughput * sky_color;

			return accumulated_light;
		    }
		}

		//Ray is absorbed(trapped) [returns black]
		return color(0, 0, 0); 	    
	    }
    };
}

#endif
