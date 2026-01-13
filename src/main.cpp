#include <iostream>

#include <ryt/graphics/color.hpp>
#include <ryt/math/vec3.hpp>
#include <ryt/math/ray.hpp>

ryt::color ray_color(const ryt::ray& r)
{
    ryt::vec3 unit_direction = ryt::unit_vector(r.direction());
    auto a = 0.5 * (unit_direction.y() + 1.0);
    
    return (1.0 - a) * ryt::color(1.0, 1.0, 1.0) + a * ryt::color(0.5, 0.7, 1.0);
}

int main()
{
    auto aspect_ratio = 16.0 / 9.0;

    int img_w = 1028;

    // calculate img_h and clamp to > 1
    int img_h = int(img_w / aspect_ratio);
    // clamp image_height to > 1
    img_h = (img_h < 1) ? 1 : img_h;

    // camera
    auto focal_length = 1.0;
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (double(img_w)/img_h);
    ryt::vec3 camera_center = ryt::vec3(0, 0, 0);

    // vectors across horizontal and vertical viewport
    ryt::vec3 viewport_u = ryt::vec3(viewport_width, 0, 0);
    ryt::vec3 viewport_v = ryt::vec3(0, -viewport_height, 0);

    // calculate pixel delta vectors
    ryt::vec3 pixel_delta_u = viewport_u / img_w;
    ryt::vec3 pixel_delta_v = viewport_v / img_h;
    
    // location of upper left pixel
    ryt::vec3 viewport_upper_left = camera_center - ryt::vec3(0, 0, focal_length) - (viewport_u/2) - (viewport_v/2);
    ryt::vec3 pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    // RENDER
    // The Below block of code renders the image
    std::cout << "P3" << std::endl << img_w << ' ' << img_h << std::endl << 255 << std::endl;

    for(int i = 0; i < img_h; i++)
    {
	// clear up line
	std::clog << '\r' << std::string(25, ' ') << '\r';
	// write progress
	std::clog << "Progress : " << ((((double)i)/(img_h-1)) * 100) << '%';

	for(int j = 0; j < img_w; j++)
	{
	    ryt::vec3 pixel_center = pixel00_loc + (j * pixel_delta_u) + (i * pixel_delta_v);
	    ryt::vec3 ray_direction = pixel_center - camera_center;
	    ryt::ray r(camera_center, ray_direction);

	    ryt::color pixel_color = ray_color(r);
	    write_color(std::cout, pixel_color);
	}
    }

    std::clog << std::endl << "Render Complete" << std::endl;

    return 0;
}
