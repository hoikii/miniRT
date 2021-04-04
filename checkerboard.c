/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerboard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 14:44:24 by kanlee            #+#    #+#             */
/*   Updated: 2021/04/05 03:16:18 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "checkerboard.h"
#include "objects.h"
#include "color.h"
#include "math_utils.h"

t_color	checker_sphere(t_rec rec)
{
	t_vec	tmp;

	tmp.x = fabs(floor(rec.normal.x * 2));
	tmp.y = fabs(floor(rec.normal.y * 2));
	tmp.z = fabs(floor(rec.normal.z * 2));
	if (((int)tmp.x % 2) ^ ((int)tmp.y % 2) ^ ((int)tmp.z % 2))
		return (color(1, 1, 1));
	return (color(0, 0, 0));
}

t_color	checker_plane(t_rec rec, t_mlx *rt)
{
	t_plane	*pl;
	t_vec	tmp;
	double	x;
	double	y;

	pl = (t_plane *)rt->objects_array[rec.obj_id].data;
	tmp = v_sub(rec.point, pl->point);
	x = fabs(floor(v_dot(pl->u, tmp)));
	y = fabs(floor(v_dot(pl->v, tmp)));
	if (((int)x % 2) ^ ((int)y % 2))
		return (color(1, 1, 1));
	return (color(0, 0, 0));
}

t_color	checker_square(t_rec rec, t_mlx *rt)
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

t_color	checker_cylinder(t_rec rec, t_mlx *rt)
{
	t_cylinder	*cy;
	t_vec		op;
	t_vec		oh;
	t_vec		or;
	double		u;
	double		v;
	t_vec tmp;

	cy = (t_cylinder *)rt->objects_array[rec.obj_id].data;
	op = v_sub(rec.point, cy->bottom);
	oh = v_mul(cy->direction, v_dot(op, cy->direction));
	or = v_sub(op, oh);
	u = v_dot(op, cy->direction);
	u = fabs(floor(u));
	v = clamp(v_dot(cy->meridian, or) / cy->radius, -1, 1);
	tmp = v_cross(cy->meridian, or);
	if (tmp.z >= 0)
		v = acos(v);
	else
		v = 2 * PI - acos(v);
	v = fabs(floor(v / PI * 2));
	if (((int)u % 2) ^ ((int)v % 2))
		return (color(1, 1, 1));
	return (color(0, 0, 0));
}
