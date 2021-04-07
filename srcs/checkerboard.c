/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerboard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 14:44:24 by kanlee            #+#    #+#             */
/*   Updated: 2021/04/07 01:29:53 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "checkerboard.h"
#include "objects.h"
#include "math_utils.h"

t_color		checker_sphere(t_rec rec)
{
	t_vec	tmp;

	tmp.x = fabs(floor(rec.normal.x * 2));
	tmp.y = fabs(floor(rec.normal.y * 2));
	tmp.z = fabs(floor(rec.normal.z * 2));
	if (((int)tmp.x % 2) ^ ((int)tmp.y % 2) ^ ((int)tmp.z % 2))
		return (color(1, 1, 1));
	return (color(0, 0, 0));
}

t_color		checker_plane(t_rec rec, t_mlx *rt)
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

t_color		checker_square(t_rec rec, t_mlx *rt)
{
	t_vec		tmp;
	t_square	*sq;
	t_vec		up;
	t_vec		right;

	sq = (t_square *)rt->objects_array[rec.obj_id].data;
	up = v_unit(sq->up);
	right = v_unit(v_cross(up, sq->normal));
	tmp.x = v_dot(v_sub(rec.point, sq->p1), right);
	tmp.y = v_dot(v_sub(rec.point, sq->p1), up);
	tmp.x = fabs(floor(tmp.x / sq->size * (int)(sq->size + 1) * 2));
	tmp.y = fabs(floor(tmp.y / sq->size * (int)(sq->size + 1) * 2));
	if ((int)(tmp.x) % 2 ^ (int)(tmp.y) % 2)
		return (color(1, 1, 1));
	return (color(0, 0, 0));
}

static void	get_cy_coords(t_cylinder *cy, t_rec rec, double *h, double *theta)
{
	t_vec	op;
	t_vec	oh;
	t_vec	or;
	t_vec	tmp;

	op = v_sub(rec.point, cy->bottom);
	oh = v_mul(cy->direction, v_dot(op, cy->direction));
	or = v_sub(op, oh);
	*h = v_dot(op, cy->direction);
	*h = fabs(floor(*h / cy->height * (int)(cy->height + 1) * 2));
	*theta = clamp(v_dot(cy->meridian, or) / cy->radius, -1, 1);
	tmp = v_cross(cy->meridian, or);
	if (tmp.z >= 0)
		*theta = acos(*theta);
	else
		*theta = 2 * PI - acos(*theta);
	*theta = fabs(floor(*theta / PI * 2));
}

t_color		checker_cylinder(t_rec rec, t_mlx *rt)
{
	t_cylinder	*cy;
	double		h;
	double		theta;

	cy = (t_cylinder *)rt->objects_array[rec.obj_id].data;
	get_cy_coords(cy, rec, &h, &theta);
	if (((int)h % 2) ^ ((int)theta % 2))
		return (color(1, 1, 1));
	return (color(0, 0, 0));
}
