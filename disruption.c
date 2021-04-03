/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disruption.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 14:44:24 by kanlee            #+#    #+#             */
/*   Updated: 2021/04/04 01:49:22 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "disruption.h"
#include "objects.h"
#include "color.h"
#include "math_utils.h"

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
	tmp.x = fabs(floor(v_dot(v_sub(rec.point, sq->p1), right) * 4 / sq->size));
	tmp.y = fabs(floor(v_dot(v_sub(rec.point, sq->p1), up) * 4 / sq->size));
	if ((int)(tmp.x) % 2 ^ (int)(tmp.y) % 2)
		return (color(1, 1, 1));
	return (color(0, 0, 0));
}

t_color			checkerboard(t_rec rec, t_mlx *rt)
{
	t_color		local_color;
	t_vec		tmp;

	local_color = color(0, 0, 0);
	if (rec.objtype == TYPE_SPHERE)
	{
		tmp.x = (int)(fabs(floor(rec.normal.x * 2))) % 2;
		tmp.y = (int)(fabs(floor(rec.normal.y * 2))) % 2;
		tmp.z = (int)(fabs(floor(rec.normal.z * 2))) % 2;
		if ((int)tmp.x ^ (int)tmp.y ^ (int)tmp.z)
			local_color = color(1, 1, 1);
	}
	else if (rec.objtype == TYPE_SQUARE)
		local_color = checker_square(rec, rt);
	else
	{
		tmp.x = (int)(fabs(floor(rec.point.x * 2))) % 2;
		tmp.y = (int)(fabs(floor(rec.point.y * 2))) % 2;
		tmp.z = (int)(fabs(floor(rec.point.z * 2))) % 2;
		if ((int)tmp.x ^ (int)tmp.y ^ (int)tmp.z)
			local_color = color(1, 1, 1);
	}
	return (local_color);
}

t_vec			wave(t_rec rec, t_ray ray)
{
	double	frequency;
	double	amplitude;
	double	rate;
	t_vec	ret;
	t_vec	tmp;

	tmp = v_sub(rec.point, ray.origin);
	frequency = rec.bonus.wave_frequency;
	amplitude = rec.bonus.wave_amplitude;
	amplitude *= 90;
	if (rec.objtype == TYPE_PLANE)
		rate = sin(v_len(tmp) * frequency) * amplitude;
	else if (rec.objtype == TYPE_SPHERE)
		rate = sin(rec.point.y * frequency) * amplitude;
	else
		rate = sin(rec.point.x * frequency) * amplitude;
	if (fabs(rec.normal.x) != 1)
		ret = v_rotate(rec.normal, v_new(1, 0, 0), rate);
	else
		ret = v_rotate(rec.normal, v_new(0, 1, 0), rate);
	return (ret);
}
