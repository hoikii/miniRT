/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disruption.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 14:44:24 by kanlee            #+#    #+#             */
/*   Updated: 2021/04/06 16:41:31 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "disruption.h"
#include "checkerboard.h"
#include "objects.h"
#include "color.h"
#include "math_utils.h"

t_color			rainbow(t_rec rec)
{
	t_color	local_color;
	t_vec	n;

	if (rec.objtype == TYPE_SPHERE || rec.objtype == TYPE_CYLINDER)
		n = v_mul(v_add(rec.normal, v_new(1, 1, 1)), 0.5);
	else
		n = v_mul(v_add(rec.raydir, v_new(1, 1, 1)), 0.5);
	local_color = (t_color){n.x, 1 - n.y, n.z};
	return (local_color);
}

t_color			checkerboard(t_rec rec, t_mlx *rt)
{
	t_color		local_color;
	t_vec		tmp;

	local_color = color(0, 0, 0);
	if (rec.objtype == TYPE_SPHERE)
		local_color = checker_sphere(rec);
	else if (rec.objtype == TYPE_PLANE)
		local_color = checker_plane(rec, rt);
	else if (rec.objtype == TYPE_SQUARE)
		local_color = checker_square(rec, rt);
	else if (rec.objtype == TYPE_CYLINDER)
		local_color = checker_cylinder(rec, rt);
	else
	{
		tmp.x = fabs(floor(rec.point.x * 2 + EPSILON));
		tmp.y = fabs(floor(rec.point.y * 2 + EPSILON));
		tmp.z = fabs(floor(rec.point.z * 2 + EPSILON));
		if (((int)tmp.x % 2) ^ ((int)tmp.y % 2) ^ ((int)tmp.z % 2))
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
