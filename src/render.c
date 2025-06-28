#include "../includes/minirt.h"

t_hit *sphere_hit( const t_vec3d *ray_origin, const t_vec3d *ray_dir, t_sphere *sp)
{
	t_hit	*hit;
	hit = malloc(sizeof(t_hit));
	// circle
	// (x-a)^2 + (y-b)^2 - r^2 = 0
	// quadratic eq
	// (ax^2 + ay^2)t^2 + (2(bxax + byay))t + (bx^2 + by^2 - r^2) = 0;
	float r = sp->diam/2;
	float a = dot_vecs(ray_dir, ray_dir);
	float b = 2.0f * dot_vecs(ray_origin, ray_dir);
	float c = dot_vecs(ray_origin, ray_origin) - r * r;

	// discriminant = t = hit distance / point
	// b^2 - 4ac
	float delta = b * b - 4.0f * a * c;
	if (delta < 0.0f)
		return NULL;
	// move from here to outside!!!!!!!!!!!!!!!!!
	hit->distance = (-b - sqrtf(delta)) / (2.0f * a);
	// hit position -> coord of intersection in range: -1 ~ 1
	hit->position = vec_x_scalar(ray_dir, hit->distance);
	hit->position = add_vecs(ray_origin, &hit->position);
	hit->direction = norm_vec(&hit->position);
	hit->rgb = sp->rgb;
	hit->shape_origin = sp->coord;
	return hit;
}

uint32_t apply_shadow(t_hit *hit, t_light *light, t_alight *ambient)
{
	t_vec3d norm;
	norm = sub_vecs(&hit->position, hit->shape_origin); // necessary?
	norm = hit->direction;

	t_vec3d light_dir = *light->coord;
	// t_vec3d light_dir = vec_x_scalar(scene->light.coord, -1);
	light_dir = norm_vec(&light_dir);

	// dot product of sphere norm and -light direction
	float light_intensity = dot_vecs(&norm, &light_dir); 
	// == cos(angle) | if angle > 90 = negative result | cos(90) == 0
	// dot product = always in -1->1 range
	// this angle is the surface angle - reflects the light

	// clamping only min, so there is no negative (if angle > 90)
	light_intensity = clamp(light_intensity, 0.0f, light_intensity);
	// change rgb to vec3d
	t_vec3d sphere_rgb = {	
		(float)hit->rgb[0],
		(float)hit->rgb[1],
		(float)hit->rgb[2]
	};
	// sphere_rgb = norm_vec(&sphere_rgb); -> appears to be not necessary
	// applying light/shadow to sphere color
	sphere_rgb = vec_x_scalar(&sphere_rgb, light_intensity);
	return (color_per_pixel(&sphere_rgb, 1));
}

/* returns closest hit of scene objs */
t_hit *trace_ray(t_vec3d *ray_dir, t_scene *scene)
{
	t_vec3d ray_origin;
	t_hit *hit = NULL;
	t_hit *temp = NULL;
	t_hit *closest_hit = NULL;

	if (scene->amount[SP] == 0)
		return NULL;
	int count = 0;
	while (count < scene->amount[SP])
	{
		ray_origin = sub_vecs(scene->cam.coord, scene->spheres[count].coord);
		hit = sphere_hit(&ray_origin, ray_dir, &scene->spheres[count]);
		if (hit)
		{
			if (!closest_hit)
				closest_hit = hit;
			else if (closest_hit && hit->distance < closest_hit->distance)
			{
				temp = closest_hit;
				closest_hit = hit;
				free(temp);
			}
			else
				free(hit);
		}
		count++;
	}

	// float color = apply_sp_color(&hit->position, scene);
	return closest_hit;
}

// add to trivec lib
t_vec3d cross_vecs(t_vec3d *a, t_vec3d *b) {
    t_vec3d result;
    result.x = a->y * b->z - a->z * b->y;
    result.y = a->z * b->x - a->x * b->z;
    result.z = a->x * b->y - a->y * b->x;
    return result;
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

// uint32_t	per_pixel(float x, float y, t_scene *scene){
// 	uint32_t pixel_color;
// 	t_vec3d *ray_origin = scene->cam.coord;
// 	t_vec3d *ray_direction;
// 	t_hit *closest_hit;
// 	// distance, coord, direction, rgb
//
// 	// ndc coords to 3d to build ray
// 	*ray_direction = get_direction(x, y, scene);
// 	// get closest intersection info
// 	closest_hit = trace_ray(ray_direction, scene);
// 	// if no intersection, return background function
// 	if (!closest_hit)
// 		return 0xff000000;
// 		// return (no_hit(0xff000000));
// 	// add shadows and color
// 	// pixel_color = apply_shadow(closest_hit, scene->light, scene->amb_light);
// 	pixel_color = apply_sp_color(&closest_hit->position, scene);
//
// 	return pixel_color;
// }
//
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
			t_vec3d ray_dir = get_direction(x, y, scene);
			hit = trace_ray(&ray_dir, scene);
			if (!hit)
				color = 0xff000000;
			else
				color = apply_shadow(hit, &scene->light, &scene->amb_light);
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
