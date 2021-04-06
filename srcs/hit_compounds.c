/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_compounds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 21:29:59 by kanlee            #+#    #+#             */
/*   Updated: 2021/04/06 18:36:44 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "objects.h"
#include "hit.h"
#include "hit_utils.h"
#include "math_utils.h"

/*
**      cylinder caps --- ray intersection
**
** P = P0 + t*d   ,     vh = top-btm
**
** top cap: (P-top)*vh = 0  &&  (P-top)^2 <= r^2
** btm cap: (P-btm)*vh = 0  &&  (P-btm)^2 <= r^20
*/

static int	hit_bottom_cap(t_cylinder *cy, t_ray ray, double tmax, t_rec *rec)
{
	t_plane	pl;
	double	r;

	pl.point = cy->bottom;
	pl.normal = cy->direction;
	pl.color = cy->color;
	r = cy->radius;
	if (hit_plane(&pl, ray, tmax, rec)
		&& v_len_squared(v_sub(rec->point, cy->bottom)) < r * r)
	{
		if (v_dot(rec->normal, ray.direction) > 0)
			rec->normal = v_mul(rec->normal, -1);
		return (1);
	}
	return (0);
}

static int	hit_top_cap(t_cylinder *cy, t_ray ray, double tmax, t_rec *rec)
{
	t_plane	pl;
	double	r;

	pl.point = cy->top;
	pl.normal = cy->direction;
	pl.color = cy->color;
	r = cy->radius;
	if (hit_plane(&pl, ray, tmax, rec)
		&& v_len_squared(v_sub(rec->point, cy->top)) < r * r)
	{
		if (v_dot(rec->normal, ray.direction) > 0)
			rec->normal = v_mul(rec->normal, -1);
		return (1);
	}
	return (0);
}

int			hit_cylinder_cap(t_cylinder *cy, t_ray ray, double tmax, t_rec *rec)
{
	int		is_hit_caps;
	t_rec	rec_caps;

	is_hit_caps = 0;
	if (hit_bottom_cap(cy, ray, tmax, &rec_caps))
	{
		is_hit_caps = 1;
		tmax = rec_caps.t;
		*rec = rec_caps;
	}
	if (hit_top_cap(cy, ray, tmax, &rec_caps))
	{
		is_hit_caps = 1;
		tmax = rec_caps.t;
		*rec = rec_caps;
	}
	if (!hit_cylinder(cy, ray, tmax, rec) && is_hit_caps == 0)
		return (0);
	rec->objtype = TYPE_CYLINDER;
	rec->bonus = cy->bonus;
	return (1);
}

int			hit_cube(t_cube *cu, t_ray ray, double tmax, t_rec *rec)
{
	int	is_hit_face;

	is_hit_face = 0;
	rec->t = tmax;
	if (hit_square(&(cu->face[0]), ray, rec->t, rec))
		is_hit_face = 1;
	if (hit_square(&(cu->face[1]), ray, rec->t, rec))
		is_hit_face = 1;
	if (hit_square(&(cu->face[2]), ray, rec->t, rec))
		is_hit_face = 1;
	if (hit_square(&(cu->face[3]), ray, rec->t, rec))
		is_hit_face = 1;
	if (hit_square(&(cu->face[4]), ray, rec->t, rec))
		is_hit_face = 1;
	if (hit_square(&(cu->face[5]), ray, rec->t, rec))
		is_hit_face = 1;
	if (!is_hit_face)
		return (0);
	rec->objtype = TYPE_CUBE;
	rec->bonus = cu->bonus;
	return (1);
}

int			hit_pyramid(t_pyramid *py, t_ray ray, double tmax, t_rec *rec)
{
	int	is_hit_face;

	is_hit_face = 0;
	rec->t = tmax;
	if (hit_triangle(&(py->face[0]), ray, rec->t, rec))
		is_hit_face = 1;
	if (hit_triangle(&(py->face[1]), ray, rec->t, rec))
		is_hit_face = 1;
	if (hit_triangle(&(py->face[2]), ray, rec->t, rec))
		is_hit_face = 1;
	if (hit_triangle(&(py->face[3]), ray, rec->t, rec))
		is_hit_face = 1;
	if (hit_triangle(&(py->face[4]), ray, rec->t, rec))
		is_hit_face = 1;
	if (hit_triangle(&(py->face[5]), ray, rec->t, rec))
		is_hit_face = 1;
	if (!is_hit_face)
		return (0);
	rec->objtype = TYPE_PYRAMID;
	rec->bonus = py->bonus;
	return (1);
}
