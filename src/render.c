#include "../includes/minirt.h"

/* returns the color of the pixel based on maths */
uint32_t per_pixel(float x, float y, t_scene *scene)
{
	// (ax^2 + ay^2)t^2 + (2(bxax + byay))t + (bx^2 + by^2 - r^2) = 0;
    // a = ray direction
    // b = ray origin
	const t_vec3d ray_origin = {0, 0, 1.0f}; // (camera)
	const t_vec3d ray_dir = {x, y, -1.0f};
	float r = 0.5f;
	float a = dot_vecs(&ray_dir, &ray_dir);
	float b = 2.0f * dot_vecs(&ray_origin, &ray_dir);
	float c = dot_vecs(&ray_origin, &ray_origin) - r * r;

	// discriminant = t = hit distance / point
	// b^2 - 4ac
	float delta = b * b - 4.0f * a * c;

    // if no intersections, its the background. no need to continue calculating
	if (delta < 0.0f)
		return 0xff000000;

	// float t0 = (-b - sqrtf(discriminant)) / (2.0f * a);
	// float t1 = (+b - sqrtf(discriminant)) / (2.0f * a);

    // t0 is the distance of the closest intersection of ray hitting sphere (its the surface the camera sees)
	float t0 = (-b - sqrtf(delta)) / (2.0f * a);
	// float t1 = (-b + sqrtf(delta)) / (2.0f * a);

    // hit position -> coord of intersection
	t_vec3d hitpos;
    hitpos = vec_x_scalar(&ray_dir, t0);
    hitpos = add_vecs(&ray_origin, &hitpos);
	t_vec3d norm;
    // get the size of sphere ray vector
    norm = sub_vecs(&hitpos, scene->spheres[0].coord);
    // in this case the sphere coord is 0, so it makes no difference

    // normalize to get the direction which the surface is pointing
	norm = norm_vec(&norm);

    t_vec3d light_dir = {-1, -1, -1};
    
    // is it necessary?
    light_dir = norm_vec(&light_dir);

    // negative light direction because we are gonna shoot a ray at light, not from light?
    light_dir = vec_x_scalar(&light_dir, -1);

    // dot product of sphere norm and -light direction
    float d = dot_vecs(&norm, &light_dir); // == cos(angle) | if angle > 90 = negative result | cos(90) == 0
    // dot product = always in -1->1 range
    // this angle is the surface angle - reflects the light

    // clamping only min, so there is no negative (if angle > 90)
    d = clamp(d, 0.0f, d);

    // rgb values between 0->1
    t_vec3d sphere_rgb = {0, 1, 0};
    sphere_rgb = vec_x_scalar(&sphere_rgb, d);
    // applying light/shadow to sphere color
	return (color_per_pixel(&sphere_rgb, 1));
}

int		render(t_scene *scene)
{
	static int count;
	uint32_t x = 0;
	uint32_t y = 0;
	int i = 0;
	float coord[2];
	while (y < HEIGHT && i < (WIDTH * HEIGHT))
	{
        x = 0;
        while (x < WIDTH)
        {
            // 0 -> 1 range
            coord[0] = ((float)x/(float)WIDTH);
            coord[1] = ((float)y/(float)HEIGHT);

            // remap screen coords, so xy(0,0) is in the middle
            coord[0] = coord[0] * 2.0f - 1.0f;
            coord[1] = (1.0 - coord[1]) * 2.0f - 1.0f;
            my_mlx_pixel_put(&scene->img, x, y, per_pixel(coord[0], coord[1], scene));
            x++;
        }
        y++;
	}
    count++;
    printf("%i\n", count);
	mlx_put_image_to_window(scene->mlx, scene->mlx_win, scene->img.img, 0, 0);
	// mlx_string_put(scene->mlx, scene->mlx_win, 5, 12, 0xFFFFFF, "render");
	return 0;
}
