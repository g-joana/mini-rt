#include "../includes/minirt.h"
#include <math.h>
#include <stdint.h>

bool sphere_hit( const t_vec3d *ray_origin, const t_vec3d *ray_dir, t_vec3d *hitpos, float r)
{
	float a = dot_vecs(ray_dir, ray_dir);
	float b = 2.0f * dot_vecs(ray_origin, ray_dir);
	float c = dot_vecs(ray_origin, ray_origin) - r * r;

	// discriminant = t = hit distance / point
	// b^2 - 4ac
	float delta = b * b - 4.0f * a * c;
	if (delta < 0.0f)
		return 0;
	float t0 = (-b - sqrtf(delta)) / (2.0f * a);
	// hit position -> coord of intersection in range: -1 ~ 1
	*hitpos = vec_x_scalar(ray_dir, t0);
	*hitpos = add_vecs(ray_origin, hitpos);
	return 1;
}

uint32_t apply_sp_color(t_vec3d *hitpos, t_scene *scene)
{
	t_vec3d norm;
	// get the size of sphere ray vector
	norm = sub_vecs(hitpos, scene->spheres[0].coord);
	// normalize to get the direction which the surface is pointing
	norm = norm_vec(&norm);

	// t_vec3d light_dir = {0, -3, -8};
	t_vec3d light_dir = *scene->light.coord;
	// t_vec3d light_dir = vec_x_scalar(scene->light.coord, -1);

	light_dir = norm_vec(&light_dir);
	// light_dir = vec_x_scalar(&light_dir, -1);

	// light_dir = vec_x_scalar(&light_dir, -1);

	// dot product of sphere norm and -light direction
	float d = dot_vecs(&norm, &light_dir); // == cos(angle) | if angle > 90 = negative result | cos(90) == 0
					       // dot product = always in -1->1 range
					       // this angle is the surface angle - reflects the light

					       // clamping only min, so there is no negative (if angle > 90)
	d = clamp(d, 0.0f, d);

	// rgb values between 0->1
	t_vec3d sphere_rgb = {	
		clamp_color(scene->spheres[0].rgb[0]),
		clamp_color(scene->spheres[0].rgb[1]),
		clamp_color(scene->spheres[0].rgb[2])
	};
	sphere_rgb = vec_x_scalar(&sphere_rgb, d);
	// applying light/shadow to sphere color
	return (color_per_pixel(&sphere_rgb, 1));
}

/* returns the color of the pixel based on maths */
uint32_t trace_ray(t_vec3d *ray_dir, t_scene *scene)
{
	// (ax^2 + ay^2)t^2 + (2(bxax + byay))t + (bx^2 + by^2 - r^2) = 0;
	// const t_vec3d ray_origin = {0, 0, 1.0f}; // (camera)


	// ray:
	const t_vec3d *ray_origin = scene->cam.coord;
	// integrate this:
	// const t_vec3d ray_dir = {x, y, -1.0f};
	// normalize?


	float r = scene->spheres[0].diam / 2;
	t_vec3d hitpos = {2, 2, 2};
	bool hit = sphere_hit(ray_origin, ray_dir, &hitpos, r); // need to find the closest t0 of all spheres (the one in front of the others
	if (!hit)
		return 0xff000000; // background color
	float color = apply_sp_color(&hitpos, scene);
	return color;
}

t_vec3d cross_vecs(t_vec3d *a, t_vec3d *b) {
    t_vec3d result;
    result.x = a->y * b->z - a->z * b->y;
    result.y = a->z * b->x - a->x * b->z;
    result.z = a->x * b->y - a->y * b->x;
    return result;
}

int		render(t_scene *scene)
{
	float aspect_ratio = (float)WIDTH / (float)HEIGHT;
	float scale = tanf(scene->cam.fov * 0.5f * M_PI / 180.0f);

	t_vec3d up = {0.0f, 1.0f, 0.0f};

	t_vec3d temp = cross_vecs(scene->cam.norm, &up);

	t_vec3d zfoward = norm_vec(scene->cam.norm);
	t_vec3d xright = norm_vec(&temp);
	t_vec3d yup = cross_vecs(&zfoward, &xright);


	static int count;
	float x = 0;
	float y = 0;
	int i = 0;
	float coord[2];
	while (y < HEIGHT && i < (WIDTH * HEIGHT))
	{
		x = 0;
		while (x < WIDTH)
		{
			// 0 -> 1 range
			coord[0] = (x/(float)WIDTH);
			coord[1] = (y/(float)HEIGHT);

			// remap screen coords, so xy(0,0) is in the middle
			// coord[0] = coord[0] * 2.0f - 1.0f;
			// coord[1] = (1.0 - coord[1]) * 2.0f - 1.0f;
			coord[0] = (coord[0] * 2.0f - 1.0f) * aspect_ratio * scale;
			coord[1] = (coord[1] * 2.0f - 1.0f) * scale;

			t_vec3d xx = vec_x_scalar(&xright, coord[0]);
			t_vec3d yy = vec_x_scalar(&yup, coord[1]);

			t_vec3d ray_dir = add_vecs(&xx, &yy);
			ray_dir = add_vecs(&ray_dir, &zfoward);
			ray_dir = norm_vec(&ray_dir);
			
			uint32_t color = trace_ray(&ray_dir, scene);
			// projection * view * transform * vertex
			my_mlx_pixel_put(&scene->img, x, y, color);
			x++;
		}
		y++;
	}
	count++;
	// printf("%i\n", count);
	mlx_put_image_to_window(scene->mlx, scene->mlx_win, scene->img.img, 0, 0);
	// mlx_string_put(scene->mlx, scene->mlx_win, 5, 12, 0xFFFFFF, "render");
	return 0;
}
