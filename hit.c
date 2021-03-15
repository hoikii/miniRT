/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 21:29:59 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/15 15:12:11 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "objects.h"
#include "hit.h"
#include "hit_utils.h"
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

/*
** Plane - Ray intersection
**
** suppose R(t) = P = P0 + td    ,  plane spot = A     ,     plane normal = n
**
** dot(AP, n) = 0
** AP * n = 0
** dot(P0 + td - OA, n) = 0
** dot(P0 - OA, n) +t * dot(d, n) = 0
** t = dot(OA - P0, n) / dot(d, n)
*/

int	hit_plane(t_plane *pl, t_ray ray, double tmax, t_rec *rec)
{
	double	t;

	if (fabs(v_dot(ray.direction, pl->normal)) <= EPSILON)
		return (0);
	t = v_dot(v_sub(pl->point, ray.origin), pl->normal)
		/ v_dot(ray.direction, pl->normal);
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

int	hit_triangle(t_triangle *tri, t_ray ray, double tmax, t_rec *rec)
{
	t_plane	pl;
	t_rec	r;

	pl.point = tri->p1;
	pl.normal = tri->normal;
	pl.color = tri->color;
	if (!hit_plane(&pl, ray, tmax, &r))
		return (0);
	if (check_edge(tri->p1, tri->p2, r.point, tri->normal)
		&& check_edge(tri->p2, tri->p3, r.point, tri->normal)
		&& check_edge(tri->p3, tri->p1, r.point, tri->normal))
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

	pl.point = sq->center;
	pl.normal = sq->normal;
	pl.color = sq->color;
	if (!hit_plane(&pl, ray, tmax, &r))
		return (0);
	if (check_edge(sq->p1, sq->p2, r.point, sq->normal)
		&& check_edge(sq->p2, sq->p3, r.point, sq->normal)
		&& check_edge(sq->p3, sq->p4, r.point, sq->normal)
		&& check_edge(sq->p4, sq->p1, r.point, sq->normal))
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

/*
**      cylinder surface --- ray intersection
**
** P = P0 + t*d   ,     vh = top-btm
**
** | (P-btm) X vh |^2 = (r*h)^2
** | (P0+t*d-btm) X vh |^2 = (r*h)^2
** | (d X vh)*t + (P0-btm) X vh |^2 = (r*h)^2
*/

int	hit_cylinder(t_cylinder *cy, t_ray ray, double tmax, t_rec *rec)
{
	double	root1;
	double	root2;
	double	t;
	t_coef	coef;

	prepare_cylinder_coef(cy, ray, &coef);
	if (quadratic_solve2(&root1, &root2, coef) == 0)
		return (0);
	if (EPSILON < root1 && is_cylinder_range(cy, ray, root1))
		t = root1;
	else if (EPSILON < root2 && is_cylinder_range(cy, ray, root2))
		t = root2;
	else
		return (0);
	if (EPSILON <= t && t < tmax)
	{
		rec->color = cy->color;
		rec->t = t;
		rec->point = ray_at(ray, t);
		rec->normal = cylinder_normal(cy, ray, t);
		if (t == root2)
			rec->normal = v_mul(rec->normal, -1);
		return (1);
	}
	return (0);
}
