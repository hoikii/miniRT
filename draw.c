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
#include "vec.h"

t_color trace_ray(t_ray ray, t_mlx *rt)
{
	t_rec rec;
	double tmax;
	int hit_flag;
	int i;
   
	tmax = DBL_MAX;
	hit_flag = 0;
	i = -1;
	while (++i < rt->objs_cnt)
	{
		if (hit(rt->objects_array[i], ray, tmax, &rec))
		{
			tmax = rec.t;
			hit_flag = 1;
		}
	}
	
	if (hit_flag) {
		t_color l = compute_light(ray, rec, rt);
		t_color result = c_mix(l, rec.color);
		return (result);
//		return (rec.color);
//		return color(255*0.5*(rec.normal.x + 1), 255*0.5*(rec.normal.y+1), 255*0.5*(rec.normal.z+1));
	}

	t_color rgb = color(0,0,0);
	return rgb;
/*
	t_vec unit = v_unit(ray.direction);
	double t = 0.5 * (unit.y + 1.0);
	rgb.r = 255 * ((1.0 - t) * 0.5 + t * 1.0);
	rgb.g = 255 * ((1.0 - t) * 0.7 + t * 1.0);
	rgb.b = 255 * ((1.0 - t) * 1.0 + t * 1.0);
	return rgb;
*/
}

void draw(t_mlx *rt)
{
	t_cam *current_cam = (t_cam *)(rt->cam_list->content);
	double vp_width = 2 * tan(degree_to_radian(current_cam->fov/2));
	double vp_height = vp_width / rt->screen_width * rt->screen_height;
	t_ray ray;
	ray.origin = current_cam->origin;

	t_vec horizontal = v_mul(current_cam->u, vp_width);
	t_vec vertical = v_mul(current_cam->v, -vp_height);

	t_vec upper_left_corner = v_add(v_sub(v_sub(current_cam->origin,
		v_div(horizontal, 2)), v_div(vertical, 2)), current_cam->direction);

	for (int i = 0; i < rt->screen_height; i++) {
		for (int j = 0; j < rt->screen_width; j++) {
			double v = (double)i / (rt->screen_height - 1);
			double u = (double)j / (rt->screen_width - 1);

			t_vec direction; 
			direction = v_add(upper_left_corner, v_mul(horizontal, u));
			direction = v_add(direction, v_mul(vertical, v));
			direction = v_sub(direction, ray.origin);

			ray.direction = direction;

			t_color color = trace_ray(ray, rt);
			set_pixel_color(rt, i, j,  color);
		}
	}
	mlx_put_image_to_window(rt->mlx, rt->win, rt->img, 0, 0);
}

