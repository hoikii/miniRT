/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 21:29:59 by kanlee            #+#    #+#             */
/*   Updated: 2020/12/20 22:28:33 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "objects.h"
#include "math_utils.h"

int	hit_sphere(t_sphere *sp, t_ray ray, double tmax, t_rec *rec)
{
	t_vec	oc;
	double	a;
	double	b;
	double	c;
	double	t;

	oc = v_sub(ray.origin, sp->center);
	a = v_dot(ray.direction, ray.direction);
	b = 2.0 * v_dot(oc, ray.direction);
	c = v_dot(oc, oc) - sp->radius * sp->radius;
	t = quadratic_solve(a, b, c);
	if (EPSILON <= t && t < tmax)
	{
		rec->color = sp->color;
		rec->t = t;
		rec->normal = v_unit(v_sub(ray_at(ray, t), sp->center));
		rec->point = ray_at(ray, t);
		return (1);
	}
	return (0);
}

int	hit_plane(t_plane *pl, t_ray ray, double tmax, t_rec *rec)
{
	double t;

	if (fabs(v_dot(ray.direction, pl->normal)) <= EPSILON)
		return (0);
	t = v_dot(v_sub(pl->point, ray.origin), pl->normal) /
			v_dot(ray.direction, pl->normal);
	if (EPSILON <= t && t < tmax)
	{
		rec->color = pl->color;
		rec->t = t;
		rec->normal = pl->normal;
		rec->point = ray_at(ray, t);
		return (1);
	}
	return (0);
}

/*
**	A+tb = L;
**	tb = L-A;
**	(L-A)/b
*/

int	check_edge(t_vec p1, t_vec p2, t_vec hit_point, t_vec normal)
{
	t_vec edge;
	t_vec v_p;

	edge = v_sub(p2, p1);
	v_p = v_sub(hit_point, p1);
	return (v_dot(normal, v_cross(edge, v_p)) >= 0.0);
}

int	hit_triangle(t_triangle *tri, t_ray ray, double tmax, t_rec *rec)
{
	t_plane	pl;
	t_rec	r;

	pl.point = tri->p1;
	pl.normal = tri->normal;
	pl.color = tri->color;
	if (!hit_plane(&pl, ray, tmax, &r))
		return (0);
//	if (r.t < EPSILON || r.t >= tmax)
//		return (0);
	if (check_edge(tri->p1, tri->p2, r.point, tri->normal) &&
			check_edge(tri->p2, tri->p3, r.point, tri->normal) &&
			check_edge(tri->p3, tri->p1, r.point, tri->normal))
	{
		rec->color = r.color;
		rec->t = r.t;
		if (v_dot(ray.direction, r.normal) < 0)
			rec->normal = r.normal;
		else
			rec->normal = v_mul(r.normal, -1);
		rec->point = r.point;
		return (1);
	}
	return (0);
}

int	hit_square(t_square *sq, t_ray ray, double tmax, t_rec *rec)
{
	t_plane	pl;
	t_rec	r;
	t_vec	dist;

	pl.point = sq->center;
	pl.normal = sq->normal;
	pl.color = sq->color;
	if (!hit_plane(&pl, ray, tmax, &r))
		return (0);
#if 0
	dist = v_sub(r.point, sq->center);
	if ((fabs(dist.x) <= sq->size / 2) && (fabs(dist.y) <= sq->size / 2) &&
		(fabs(dist.z) <= sq->size / 2))
	{
		rec->color = r.color;
		rec->t = r.t;
		if (v_dot(ray.direction, r.normal) < 0)
			rec->normal = r.normal;
		else
			rec->normal = v_mul(r.normal, -1);
		rec->point = r.point;
		return (1);
	}
#endif
	if (check_edge(sq->p1, sq->p2, r.point, sq->normal) &&
			check_edge(sq->p2, sq->p3, r.point, sq->normal) &&
			check_edge(sq->p3, sq->p4, r.point, sq->normal) &&
			check_edge(sq->p4, sq->p1, r.point, sq->normal))
	{
		rec->color = r.color;
		rec->t = r.t;
		if (v_dot(ray.direction, r.normal) < 0)
			rec->normal = r.normal;
		else
			rec->normal = v_mul(r.normal, -1);
		rec->point = r.point;
		return (1);
	}
	return (0);
}

int	hit(t_objects obj, t_ray ray, double tmax, t_rec *rec)
{
	if (obj.type == TYPE_SPHERE)
		return (hit_sphere(obj.data, ray, tmax, rec));
	if (obj.type == TYPE_PLANE)
		return (hit_plane(obj.data, ray, tmax, rec));
	if (obj.type == TYPE_TRIANGLE)
		return (hit_triangle(obj.data, ray, tmax, rec));
	if (obj.type == TYPE_SQUARE)
		return (hit_square(obj.data, ray, tmax, rec));
	return (0);
}
