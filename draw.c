#include <float.h>
#include "minirt.h"
#include "ray.h"
#include "camera.h"
#include "sphere.h"
#include "plane.h"
#include "light.h"
#include "key.h"
#include "math_utils.h"
#include "objects.h"

t_color trace_ray(t_ray ray, t_mlx *rt)
{
	t_list *objects = rt->objects;
	t_color rgb;
	t_rec rec;
	t_vec unit = v_unit(ray.direction);
	double tmax = DBL_MAX;
	int hit = 0;
	t_list *head_bak = objects;

	for (int i = 0; i < rt->objs_cnt; i++)
	{
		if (rt->objects_array[i].type == TYPE_SPHERE) {
			if ( hit_sphere( (t_sphere *)(rt->objects_array[i].data), ray, tmax, &rec) > 0.1) {
				tmax = rec.t;
				hit = 1;
			}
		}
		if (rt->objects_array[i].type == TYPE_PLANE) {
			if ( hit_plane( (t_plane *)(rt->objects_array[i].data), ray, tmax, &rec) > 0.1) {
				tmax = rec.t;
				hit = 1;
			}
		}
		if (rt->objects_array[i].type == TYPE_TRIANGLE) {
			if ( hit_triangle( (t_triangle *)(rt->objects_array[i].data), ray, tmax, &rec) > 0.1) {
				tmax = rec.t;
				hit = 1;
			}
		}
	}

	
	if (hit) {
		t_color l = compute_light(ray, rec, rt);
		t_color result = c_mix(l, rec.color);
		return (result);
//		return (rec.color);
//		return color(255*0.5*(rec.normal.x + 1), 255*0.5*(rec.normal.y+1), 255*0.5*(rec.normal.z+1));
	}


	return rgb;
/*
	double t = 0.5 * (unit.y + 1.0);
	rgb.r = 255 * ((1.0 - t) * 0.5 + t * 1.0);
	rgb.g = 255 * ((1.0 - t) * 0.7 + t * 1.0);
	rgb.b = 255 * ((1.0 - t) * 1.0 + t * 1.0);
	return rgb;
*/
}

t_vec rotateX(t_vec a, double rad) {
	t_vec ret;

	ret.x = a.x * cos(rad) - a.z * sin(rad);
	ret.y = a.y;
	ret.z = a.x * sin(rad) + a.z * cos(rad);
	return ret;
}

t_vec rotateY(t_vec a, double rad) {
	t_vec ret;

	ret.x = a.x;
	ret.y = a.y * cos(rad) - a.z * sin(rad);
	ret.z = a.y * sin(rad) + a.z * cos(rad);
	return ret;
}

void draw(t_mlx *rt)
{
	double ratio = (double)rt->screen_width / rt->screen_height;

	rt->cam.fov = clamp(rt->cam.fov, 0, 180);
	double fov = rt->cam.fov;
	double vp_width = 2 * tan(degree_to_radian(fov/2));
	double vp_height = vp_width / ratio;
#if 0
	x' = cos0 -sin0 x
	y' = sin0 cos0  y
#endif

//printf("\rtx:%f, ty:%f", rt->cam.tanx, rt->cam.tany);
	rt->cam.direction = rotateY(v_new(0,0,1), degree_to_radian(rt->cam.tany));
	rt->cam.direction = rotateX(rt->cam.direction, degree_to_radian(rt->cam.tanx));
	rt->cam.direction = v_unit(rt->cam.direction);
	rt->cam.vup = rotateY(v_new(0,1,0), degree_to_radian(rt->cam.tany));
	rt->cam.vup = rotateX(rt->cam.vup, degree_to_radian(rt->cam.tanx));
	rt->cam.vup = v_unit(rt->cam.vup);


	t_vec vup = rt->cam.vup;
	t_vec u = v_unit(v_cross(vup, rt->cam.direction));
	t_vec v = v_cross(rt->cam.direction, u);
	rt->cam.origin = v_add(v_add(rt->cam.origin, v_mul(u, rt->cam.offsetX)), v_mul(rt->cam.direction, rt->cam.offsetZ));
	t_vec origin = rt->cam.origin;
	rt->cam.offsetX = rt->cam.offsetZ = 0;
	t_vec horizontal = v_mul(u, vp_width);
	t_vec vertical = v_mul(v, -vp_height);

//	double vp_height = 2.0;
//	double vp_width = vp_height * ratio;
	double focal_length = 1.0;
//	t_vec origin = v_new(0,0,0);
//	t_vec horizontal = v_new(vp_width, 0, 0);
//	t_vec vertical = v_new(0, -vp_height, 0);
	t_vec upper_left_corner = v_add(v_sub(v_sub(origin, v_div(horizontal, 2)), 
				v_div(vertical, 2)), rt->cam.direction);


#if 0
	t_ambient ambient;
	ambient.brightness = 0.2;
	ambient.color = color(0.6, 0.6, 0.6);
	t_light light[2];
	light[0].position = v_new(-3,0.6,-0.6);
	light[0].brightness = 0.9;
	light[0].color = color(1, 1, 1);
	light[1].position = v_new( 3,0.6,-0.6);
	light[1].brightness = 0.9;
	light[1].color = color(1, 1, 1);
#endif

	for (int i = 0; i < rt->screen_height; i++) {
		for (int j = 0; j < rt->screen_width; j++) {
			double v = (double)i / (rt->screen_height - 1);
			double u = (double)j / (rt->screen_width - 1);

			t_vec direction; 
			direction = v_add(upper_left_corner, v_mul(horizontal, u));
			direction = v_add(direction, v_mul(vertical, v));
			direction = v_sub(direction, origin);

			t_ray ray;
			ray.origin = origin;
			ray.direction = direction;

			t_color color = trace_ray(ray, rt);
			set_pixel_color(rt, i, j,  color);
		}
	}
	mlx_put_image_to_window(rt->mlx, rt->win, rt->img, 0, 0);
}

