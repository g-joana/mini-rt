#include "../includes/minirt.h"

t_hit *sphere_hit( const t_vec3d *ray_origin, const t_vec3d *ray_dir, t_sphere *sp)
{
	t_hit	*hit;
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
	hit = malloc(sizeof(t_hit));
	hit->distance = (-b - sqrtf(delta)) / (2.0f * a);
	return hit;
}

t_hit *cylinder_hit( const t_vec3d *ray_origin, const t_vec3d *ray_dir, t_cylinder *cylin)
{
	t_hit	*hit;

	// all norm should be normalized on parser
	t_vec3d half_height_ratio = vec_x_scalar(cylin->norm, cylin->height / 2.0f);
	t_vec3d base = sub_vecs(cylin->coord, &half_height_ratio);
	t_vec3d top = add_vecs(cylin->coord, &half_height_ratio);
	t_vec3d oc = sub_vecs(ray_origin, &base);

	float da = dot_vecs(ray_dir, cylin->norm);
	float oca = dot_vecs(&oc, cylin->norm);


	t_vec3d d_perp = vec_x_scalar(cylin->norm, da);
	d_perp = sub_vecs(ray_dir, &d_perp);
	t_vec3d oc_perp = vec_x_scalar(cylin->norm, oca);
	oc_perp = sub_vecs(&oc, &oc_perp);

	t_vec3d o = oc_perp;
	t_vec3d d = d_perp;

	float r = cylin->diam/2;
	float a = dot_vecs(&d, &d);
	float b = 2.0f * dot_vecs(&o, &d);
	float c = dot_vecs(&o, &o) - (r * r);
	// float c = dot_vecs(ray_origin, ray_origin) - r * r;

	// discriminant = t = hit distance / point
	// b^2 - 4ac
	float delta = b * b - 4.0f * a * c;
	if (delta < 0.0f)
		return NULL;
	hit = malloc(sizeof(t_hit));
	hit->distance = (-b - sqrtf(delta)) / (2.0f * a);


	t_vec3d hit_point = {
		ray_origin->x + ray_dir->x * hit->distance,
		ray_origin->y + ray_dir->y * hit->distance,
		ray_origin->z + ray_dir->z * hit->distance
	};

	// Vector from base to hit point
	t_vec3d base_to_hit = sub_vecs(&hit_point, &base);

	// Project onto cylinder axis to get height along axis
	float axis_dist = dot_vecs(&base_to_hit, cylin->norm);

	if (axis_dist < 0.0f || axis_dist > cylin->height)
	{
		free(hit);
		return NULL;
	}


	// calculate y position of the hit point
	// y = ray_origin.y + ray_dir.y * t
	//float half_h = cylin->height / 2.0f;
	//float y = ray_origin->y + ray_dir->y * hit->distance;
	//if (y < -half_h || y > half_h)
	//	return NULL;


	return hit;
}

t_hit *set_cylinder_hit(t_vec3d *ray_dir, t_scene *scene, int id)
{
	t_vec3d ray_origin;
	t_hit *hit;

	ray_origin = sub_vecs(scene->cam.coord, scene->cylinders[id].coord);
	hit = cylinder_hit(&ray_origin, ray_dir, &scene->cylinders[id]);
	hit->rgb = scene->cylinders[id].rgb;
	hit->shape_origin = scene->cylinders[id].coord;
	hit->position = vec_x_scalar(ray_dir, hit->distance);
	hit->position = add_vecs(&ray_origin, &hit->position);
	// closest->position = norm_vec(&hit->position);
	hit->direction = norm_vec(&hit->position);
	return (hit);
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

t_hit *set_sphere_hit(t_vec3d *ray_dir, t_scene *scene, int id)
{
	t_vec3d ray_origin;
    t_hit *hit;

    ray_origin = sub_vecs(scene->cam.coord, scene->spheres[id].coord);
    hit = sphere_hit(&ray_origin, ray_dir, &scene->spheres[id]);
    hit->rgb = scene->spheres[id].rgb;
    hit->shape_origin = scene->spheres[id].coord;
    hit->position = vec_x_scalar(ray_dir, hit->distance);
    hit->position = add_vecs(&ray_origin, &hit->position);
    // closest->position = norm_vec(&hit->position);
    hit->direction = norm_vec(&hit->position);
    return (hit);
}

/* returns closest hit of scene objs */
t_hit *trace_ray(t_vec3d *ray_dir, t_scene *scene)
{
	t_vec3d ray_origin;
	t_hit *hit;
	int id = -1;
	int shape = -1;
	float distance = FLT_MAX;

	int count = 0;
	while (count < scene->amount[SP])
	{
		ray_origin = sub_vecs(scene->cam.coord, scene->spheres[count].coord);
		hit = sphere_hit(&ray_origin, ray_dir, &scene->spheres[count]);
		if (hit && hit->distance > 0.0f && hit->distance < distance)
		{
			distance = hit->distance;
			id = count;
			shape = SP;
			free(hit);
		}
		count++;
	}
	count = 0;
	while (count < scene->amount[CY])
	{
		ray_origin = sub_vecs(scene->cam.coord, scene->cylinders[count].coord);
		hit = cylinder_hit(&ray_origin, ray_dir, &scene->cylinders[count]);
		if (hit && hit->distance > 0.0f && hit->distance < distance)
		{
			distance = hit->distance;
			id = count;
			shape = CY;
			free(hit);
		}
		count++;
	}
	if (id == -1)
		return NULL;
	if (shape == SP)
		hit = set_sphere_hit(ray_dir, scene, id);
	else if (shape == CY)
		hit = set_cylinder_hit(ray_dir, scene, id);
	return hit;
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
			free(hit);
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
