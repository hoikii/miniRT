/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disruption.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 14:44:24 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/26 03:49:21 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "minirt.h"
#include "objects.h"
#include "color.h"
#include "math_utils.h"

#define BLACK {0,0,0}
#define WHITE {1,1,1}

t_color			rainbow(t_rec rec)
{
	t_color	local_color;
	t_vec	n;

	if (rec.objtype == TYPE_PLANE)
		n = v_mul(v_add(rec.raydir, v_new(1, 1, 1)), 0.5);
	else
		n = v_mul(v_add(rec.normal, v_new(1, 1, 1)), 0.5);
	local_color = (t_color){n.x, 1 - n.y, n.z};
	return (local_color);
}

static t_color	checker_square(t_rec rec, t_mlx *rt)
{
	t_vec		tmp;
	t_square	*sq;
	t_vec		up;
	t_vec		right;

	sq = (t_square *)rt->objects_array[rec.obj_id].data;
	up = v_mul(sq->up, sq->size / 2);
	right = v_cross(up, sq->normal);
	tmp.x = fabs(floor(v_dot(v_sub(rec.point, sq->p1), right) *4 / sq->size));
	tmp.y = fabs(floor(v_dot(v_sub(rec.point, sq->p1), up) *4 / sq->size));
	if ((int)(tmp.x) % 2 ^ (int)(tmp.y) % 2)
		return ((t_color)WHITE);
	return ((t_color)BLACK);
}

t_color			checkerboard(t_rec rec, t_mlx *rt)
{
	t_color		local_color;
	t_vec		tmp;

	local_color = (t_color)BLACK;
	if (rec.objtype == TYPE_SPHERE)
	{
		tmp.x = (int)(fabs(floor(rec.normal.x * 2 ))) % 2;
		tmp.y = (int)(fabs(floor(rec.normal.y * 2 ))) % 2;
		tmp.z = (int)(fabs(floor(rec.normal.z * 2 ))) % 2;
		if ((int)tmp.x ^ (int)tmp.y ^ (int)tmp.z)
			local_color = (t_color)WHITE;
	}
	else if (rec.objtype == TYPE_SQUARE)
		local_color = checker_square(rec, rt);
	else
	{
		tmp.x = (int)(fabs(floor(rec.point.x * 2 ))) % 2;
		tmp.y = (int)(fabs(floor(rec.point.y * 2 ))) % 2;
		tmp.z = (int)(fabs(floor(rec.point.z * 2 ))) % 2;
		if ((int)tmp.x ^ (int)tmp.y ^ (int)tmp.z)
			local_color = (t_color)WHITE;
	}
	return (local_color);
}

/*
** SinA + SinB = 2*Sin((A+B)/2)*COS((A-B)/2)
*/

t_vec	wave(t_rec rec, t_mlx *rt)
{
#if 0
	double	sinn;
	double	scal;
	t_vec	ret;

	scal = 60 * v_len(v_sub(rec.point, ray_origin));
	sinn = sin(rec.point.z * scal) + sin(rec.point.y * scal);
	ret = v_rotate(rec.normal, v_new(1, 0, 0), sinn);
	return (ret);
#endif
#if 1
	t_vec	tmp;
	double	frequency;
	double	amplitude;
	t_vec	ret;
	
	frequency = 50;
	amplitude = 0.01;
	frequency = 30;
	amplitude = 0.03;
//	frequency = rt->frequency;
//	amplitude = clamp(rt->amplitude, 0, 0.2);
	amplitude *= 90;
	tmp.x = sin(rec.point.x * frequency) * amplitude;
	ret = v_rotate(rec.normal, v_new(1, 0, 0), tmp.x);
	return (ret);
#endif
#if 0
	t_vec	wave_n;
	double	alpha;
	double	d;

	wave_n = v_sub(ray_origin, rec.point);
	d = v_len(wave_n);
	alpha = 100 * exp(-d * 0.025) * cos(0.25 * PI * d);
	wave_n = v_sub(rec.point, ray_origin);
	wave_n.x *= alpha;
	wave_n.z *= alpha;
	wave_n.y = 100;
	return (v_unit(wave_n));
#endif
}
