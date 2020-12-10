/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 08:48:30 by kanlee            #+#    #+#             */
/*   Updated: 2020/12/10 09:58:47 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void			set_pixel_color(t_mlx *rt, int y, int x, t_color tcolor)
{
	char	*imgdata;
	int		color;
	int		pos;

	imgdata = rt->imgdata;
//	color = mlx_get_color_value(rt->mlx, rgb_to_int(_color.r, _color.g, _color.b));
	color = color_to_int(tcolor);
	pos = y * rt->size_line + x * rt->bpp / 8;
	imgdata[pos + 0] = color;
	imgdata[pos + 1] = color >> 8;
	imgdata[pos + 2] = color >> 16;
	return ;
}

t_color			trace_ray(t_ray ray, t_mlx *rt)
{
	t_rec	rec;
	double	tmax;
	int		hit_flag;
	int		i;
	t_color	result;

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
	if (hit_flag)
	{
		result = c_mix(rec.color, compute_light(ray, rec, rt));
		return (result);
	}
	return (color(0, 0, 0));
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

void			draw(t_mlx *rt)
{
	int			i;
	int			j;
	t_ray		ray;
	t_viewport	vp;

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
			set_pixel_color(rt, i, j, trace_ray(ray, rt));
		}
	}
	mlx_put_image_to_window(rt->mlx, rt->win, rt->img, 0, 0);
}
