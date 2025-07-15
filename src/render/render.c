#include "../../includes/minirt.h"

uint32_t apply_light(t_hit *hit, t_light *light, t_alight *ambient)
{
	t_vec3d norm;
	norm = hit->direction;

	t_vec3d light_dir = sub_vecs(light->coord, &hit->position);
	light_dir = norm_vec(&light_dir);

	// dot product of sphere norm and -light direction
	float light_intensity = dot_vecs(&norm, &light_dir); 
	// == cos(angle) | if angle > 90 = negative result | cos(90) == 0
	// dot product = always in -1->1 range
	// this angle is the surface angle - reflects the light

	// clamping only min, so there is no negative (if angle > 90)
	light_intensity = clamp(light_intensity, 0.0f, light_intensity);
	// change rgb to vec3d
	t_vec3d rgb = {	
		(float)hit->rgb[0],
		(float)hit->rgb[1],
		(float)hit->rgb[2]
	};

	t_vec3d ambient_rgb = {
		rgb.x * ambient->bright,
		rgb.y * ambient->bright,
		rgb.z * ambient->bright
	};
	// sphere_rgb = norm_vec(&sphere_rgb); -> appears to be not necessary
	// applying light/shadow to sphere color
	rgb = vec_x_scalar(&rgb, light_intensity * light->bright); // spot
	// rgb = add_vecs(&rgb , &ambient_rgb);
	return (color_per_pixel(&rgb, 1));
}

/* returns closest hit of scene objs */
t_hit *trace_ray(t_vec3d *ray_dir, t_scene *scene)
{
	t_hit *hit;
	t_hit *closest = NULL;
	int shape = PL;
	float distance = FLT_MAX;

	int count = 0;
	while (shape <= CY)
	{
        count = 0;
        while (count < scene->amount[shape])
        {
            hit = get_shape_hit(ray_dir, scene, shape, count);
            if (hit && hit->distance > 0.0f && hit->distance < distance)
            {
                if (closest)
                    free(closest);
                distance = hit->distance;
                closest = hit;
                closest->id = count;
            }
            else
                free(hit);
            count++;
        }
        shape++;
    }
	set_shape_hit(ray_dir, scene, closest);
	return closest;
}

t_vec3d	get_direction(float x, float y, t_scene *scene) {
	float u;
	float v;

	// aspect_ratio makes image not distort in different screen sizes by saving propotions on ratio
	// scale is how much the camera is able to see (vertically) based on fov angle (zoom out/in)
	// tangent of fov/2 (the midle) in radians
	// (fov / 2.0f) -> gets half fov
	// (M_PI / 180.0f) -> converts degrees into radians
	// tanf( radians of the target ) ->
	u = (x/(float)WIDTH);
	v = (y/(float)HEIGHT);
	// 2d ndc -> 3d world coords
	// projection * view * transform * vertex
	u = (u * 2.0f - 1.0f) * scene->aspect_ratio * scene->scale;
	v = (v * 2.0f - 1.0f) * scene->scale;

	t_vec3d x_dir = vec_x_scalar(scene->cam.right, u);
	t_vec3d y_dir = vec_x_scalar(scene->cam.up, v);

	t_vec3d ray_dir = add_vecs(&x_dir, &y_dir);
	ray_dir = add_vecs(&ray_dir, scene->cam.foward);
	ray_dir = norm_vec(&ray_dir);

	return ray_dir;
}

u_int32_t	perpixel(float x, float y, t_scene* scene) // raygen -> ray trace pipeline / shaders
{
	u_int32_t color;
	t_hit *closest_hit;
	t_vec3d ray_dir = get_direction(x, y, scene);

	closest_hit = trace_ray(&ray_dir, scene);
	if (!closest_hit)
		color = 0xff007fff; // background / miss shader
	else
		color = apply_light(closest_hit, &scene->light, &scene->amb_light);
	free(closest_hit);
	return color;
}

int		render(t_scene *scene)
{
	static int count;
	float x = 0;
	float y = 0;
	t_hit *hit;
	u_int32_t color;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			color = perpixel(x, y, scene);
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
