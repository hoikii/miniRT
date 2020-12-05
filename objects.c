/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 21:29:59 by kanlee            #+#    #+#             */
/*   Updated: 2020/12/02 13:57:31 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "objects.h"

int hit_sphere(t_sphere *sp, t_ray ray, double tmax, t_rec *rec)
{
	t_vec center = sp->center;
	double radius = sp->radius;
	t_vec oc = v_sub(ray.origin, center);
	double a = v_dot(ray.direction, ray.direction);
	double b = 2.0 * v_dot(oc, ray.direction);
	double c = v_dot(oc, oc) - radius * radius;
	double discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (0);
	double t = (-b - sqrt(discriminant)) / (2.0 * a);
	if (t < 0)
		t = (-b + sqrt(discriminant)) / (2.0 * a);
	if (EPSILON <= t && t < tmax) {
		rec->color = sp->color;
		rec->t = t;
		rec->normal = v_unit(v_sub(ray_at(ray, t), center));
		rec->point = ray_at(ray, t);
		return (1);
	}
	return (0);
}

#if 0
  t =( A.h - O.h ) / (d.h)
 
#endif

int hit_plane(t_plane *pl, t_ray ray, double tmax, t_rec *rec)
{
	if (fabs(v_dot(ray.direction, pl->normal)) <= EPSILON)
		return (0);
//	double t = (v_dot(pl->point, pl->normal) - v_dot(ray.origin, pl->normal)) / v_dot(ray.direction, pl->normal);
	double t = v_dot(v_sub(pl->point,ray.origin), pl->normal) / v_dot(ray.direction, pl->normal);
	if (EPSILON <= t && t < tmax) {
		rec->color = pl->color;
		rec->t = t;
		rec->normal = pl->normal;
		rec->point = ray_at(ray, t);
		return (1);
	}
	return (0);
}


/*
	A+tb = L;
	tb = L-A;
	(L-A)/b
*/

int check_edge(t_vec p1, t_vec p2, t_vec hit_point, t_vec normal)
{
	t_vec edge = v_sub(p2, p1);
	t_vec v_p = v_sub(hit_point, p1);
	return ( v_dot(normal,  v_cross(edge, v_p)) >= 0.0 );
}


int hit_triangle(t_triangle *tri, t_ray ray, double tmax, t_rec *rec)
{
	t_plane pl;
	pl.point = tri->p1;
	pl.normal = tri->normal;
	pl.color = tri->color;
	t_rec r;
	if (!hit_plane(&pl, ray, tmax, &r))
		return (0);
	if (r.t < EPSILON || r.t >= tmax)
		return (0);
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

int hit(t_objects obj, t_ray ray, double tmax, t_rec *rec)
{
	if (obj.type == TYPE_SPHERE)
		return (hit_sphere(obj.data, ray, tmax, rec));
	if (obj.type == TYPE_PLANE)
		return (hit_plane(obj.data, ray, tmax, rec));
	if (obj.type == TYPE_TRIANGLE)
		return (hit_triangle(obj.data, ray, tmax, rec));
	return (0);
}


