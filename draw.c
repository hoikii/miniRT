/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 08:48:30 by kanlee            #+#    #+#             */
/*   Updated: 2021/01/28 16:38:19 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <float.h>
#include <pthread.h>
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
#include <stdio.h>

void			set_pixel_color(t_cam *cam, int y, int x, t_color tcolor)
{
	char	*imgdata;
	int		color;
	int		pos;

	imgdata = cam->image.imgdata;
//	color = mlx_get_color_value(rt->mlx, rgb_to_int(_color.r, _color.g, _color.b));
	color = color_to_int(tcolor);
	pos = y * cam->image.size_line + x * cam->image.bpp / 8;
	imgdata[pos + 0] = color;
	imgdata[pos + 1] = color >> 8;
	imgdata[pos + 2] = color >> 16;
	return ;
}

int				hit_nearest_object(t_mlx *rt, t_ray ray, t_rec *rec)
{
	int		i;
	int		ret;
	double	tmax;

	tmax = DBL_MAX;
	ret = 0;
	i = -1;
	while (++i < rt->objs_cnt)
	{
		if (hit(rt->objects_array[i], ray, tmax, rec))
		{
			tmax = rec->t;
			rec->raydir = ray.direction;
			ret = 1;
		}
	}
	return (ret);
}

t_color			trace_ray(t_ray ray, int depth, t_mlx *rt)
{
	t_rec	rec;
	t_color	local_color;
	t_color	reflected_color;
	t_vec	reflect_dir;
	double	r;

	if (!hit_nearest_object(rt, ray, &rec))
		return (color(0, 0, 0));
	local_color = apply_light(ray, rec, rt->lights_list, rt);
	r = 0.1;
	if (depth <= 0 || r <= 0)
		return (local_color);
	reflect_dir = v_sub(ray.direction, 
			v_mul(rec.normal, v_dot(rec.normal, ray.direction) * 2));
	reflected_color = trace_ray(new_ray(rec.point, reflect_dir), depth - 1, rt);
	return c_add(c_mul(local_color, 1 - r), c_mul(reflected_color, r));
}

/*
**	t_vec unit = v_unit(ray.direction);
**	double t = 0.5 * (unit.y + 1.0);
**	rgb.r = 255 * ((1.0 - t) * 0.5 + t * 1.0);
**	rgb.g = 255 * ((1.0 - t) * 0.7 + t * 1.0);
**	rgb.b = 255 * ((1.0 - t) * 1.0 + t * 1.0);
**	return rgb;
*/

static void		set_viewport(t_mlx *rt, t_viewport *vp)
{
	t_cam	*cam;
	double	vp_width;
	double	vp_height;

	cam = (t_cam *)(rt->cam_list->content);
	vp_width = 2 * tan(degree_to_radian(cam->fov / 2));
	vp_height = vp_width / rt->screen_width * rt->screen_height;
	vp->horizontal = v_mul(cam->u, vp_width);
	vp->vertical = v_mul(cam->v, -vp_height);
	vp->upper_left_corner = v_sub(v_sub(v_add(cam->origin, cam->direction),
		v_div(vp->horizontal, 2)), v_div(vp->vertical, 2));
	return ;
}

static t_vec	set_ray_direction(t_ray ray, t_viewport vp, double y, double x)
{
	t_vec direction;

	direction = v_add(vp.upper_left_corner, v_mul(vp.horizontal, x));
	direction = v_add(direction, v_mul(vp.vertical, y));
	direction = v_sub(direction, ray.origin);
	return (direction);
}



void			*draw_thread(void *arg)
{
	int			i;
	int			j;
	t_ray		ray;
	t_viewport	vp;
int depth = 1;
	t_mlx *rt;
	rt = ((t_thread *)arg)->mlx;
	int tid = ((t_thread *)arg)->tid;
printf("tid:%d\n", tid);

	set_viewport(rt, &vp);
	ray.origin = ((t_cam *)(rt->cam_list->content))->origin;
	i = -1;
	while (++i < rt->screen_height)
	{
		if (i % THREADS_CNT == tid)
			continue;
		j = -1;
		while (++j < rt->screen_width)
		{
			ray.direction = set_ray_direction(ray, vp,
					(double)i / (rt->screen_height - 1),
					(double)j / (rt->screen_width - 1));
			//set_pixel_color(rt, i, j, trace_ray(ray, depth, rt));
			set_pixel_color(rt->cam_list->content, i, j, trace_ray(ray, depth, rt));
		}
	}
	pthread_exit((void *)0);
}



void			draw_thread_entry(t_mlx *rt)
{
	pthread_t	threads[THREADS_CNT];
	t_thread	arg[THREADS_CNT];
	int			i;

	i = -1;
	while (++i < THREADS_CNT)
	{
		arg[i].mlx = rt;
		arg[i].tid = i;
		pthread_create(&threads[i], NULL, &draw_thread, (void *)(&arg[i]));
	}
	while (--i >= 0)
		pthread_join(threads[i], NULL);
	mlx_put_image_to_window(rt->mlx, rt->win, rt->cam_list->content->image.img, 0, 0);
}

void			draw(t_mlx *rt)
{
	int			i;
	int			j;
	t_ray		ray;
	t_viewport	vp;
int depth = 3;

	set_viewport(rt, &vp);
	ray.origin = ((t_cam *)(rt->cam_list->content))->origin;
	i = -1;
	while (++i < rt->screen_height)
	{
		j = -1;
		while (++j < rt->screen_width)
		{
			ray.direction = set_ray_direction(ray, vp,
					(double)i / (rt->screen_height - 1),
					(double)j / (rt->screen_width - 1));
			//set_pixel_color(rt, i, j, trace_ray(ray, depth, rt));
			set_pixel_color(rt->cam_list->content, i, j, trace_ray(ray, depth, rt));
		}
	}
	mlx_put_image_to_window(rt->mlx, rt->win, rt->cam_list->content->image.img, 0, 0);
}
