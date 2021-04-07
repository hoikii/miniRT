/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 08:48:30 by kanlee            #+#    #+#             */
/*   Updated: 2021/04/07 02:07:33 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include "minirt.h"
#include "ray.h"
#include "camera.h"
#include "light.h"
#include "math_utils.h"
#include "objects.h"
#include "vec.h"
#include "disruption.h"
#include "uv_mapping.h"

static int	hit_nearest_object(t_mlx *rt, t_ray ray, t_rec *rec)
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
			rec->obj_id = i;
			ret = 1;
		}
	}
	return (ret);
}

void		set_viewport(t_mlx *rt)
{
	t_cam		*cam;
	t_viewport	*vp;
	double		vp_width;
	double		vp_height;

	cam = (t_cam *)(rt->cam_list->content);
	vp = &(cam->vp);
	vp_width = 2 * tan(degree_to_radian(cam->fov / 2));
	vp_height = vp_width / rt->screen_width * rt->screen_height;
	vp->horizontal = v_mul(cam->u, vp_width);
	vp->vertical = v_mul(cam->v, -vp_height);
	vp->upper_left_corner = v_sub(v_sub(v_add(cam->origin, cam->direction),
				v_div(vp->horizontal, 2)), v_div(vp->vertical, 2));
	return ;
}

t_vec		set_ray_direction(t_ray ray, double y, double x, t_mlx *rt)
{
	t_vec	direction;
	t_cam	*cam;

	cam = (t_cam *)(rt->cam_list->content);
	y = y / (rt->screen_height - 1);
	x = x / (rt->screen_width - 1);
	direction = v_add(cam->vp.upper_left_corner, v_mul(cam->vp.horizontal, x));
	direction = v_add(direction, v_mul(cam->vp.vertical, y));
	direction = v_sub(direction, ray.origin);
	return (v_unit(direction));
}

void		set_pixel_color(t_mlx *rt, int y, int x, t_color color)
{
	t_cam			*cam;
	char			*imgdata;
	unsigned int	color_value;
	int				pos;

	cam = rt->cam_list->content;
	imgdata = cam->image.imgdata;
	color_value = mlx_get_color_value(rt->mlx, color_to_int(color));
	pos = y * cam->image.size_line + x * cam->image.bpp / 8;
	imgdata[pos + 0] = color_value;
	imgdata[pos + 1] = color_value >> 8;
	imgdata[pos + 2] = color_value >> 16;
	return ;
}

t_color		trace_ray(t_ray ray, int depth, t_mlx *rt)
{
	t_rec	rec;
	t_color	local_color;
	t_color	reflected_color;
	t_vec	reflect_dir;
	double	r;

	if (!hit_nearest_object(rt, ray, &rec))
	{
		if (BONUS && rt->skybox_declared)
			return (skymap(ray.direction, rt));
		return (color(0, 0, 0));
	}
	if (BONUS && rec.bonus.texture_type == TEXTURE_WAVE)
		rec.normal = wave(rec, ray);
	local_color = apply_light(rec, -1, rt);
	r = 0;
	if (BONUS)
		r = rec.bonus.refl_rate;
	if (depth <= 0 || r <= 0)
		return (local_color);
	reflect_dir = v_sub(ray.direction,
			v_mul(rec.normal, v_dot(rec.normal, ray.direction) * 2));
	reflected_color = trace_ray(new_ray(rec.point, reflect_dir), depth - 1, rt);
	return (c_add(c_mul(local_color, 1 - r), c_mul(reflected_color, r)));
}
