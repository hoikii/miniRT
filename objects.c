/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 21:29:59 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/10 12:46:32 by kanlee           ###   ########.fr       */
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

	pl.point = sq->center;
	pl.normal = sq->normal;
	pl.color = sq->color;
	if (!hit_plane(&pl, ray, tmax, &r))
		return (0);
#if 0
	t_vec	dist;
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

/*     cylinder surface --- ray intersection
** bottom + u*h*dir + r  = P0 + td   ( 0<=u<=1) .....1
** bottom*dir + u*h*dir*dir = P0*dir + t*d*dir  (since dir*r=0)
** u = (P0*dir + t*d*dir - bottom*dir) / (h*dir*dir) .....2
** r = P0 + td - bottom - ((P0*dir + t*d*dir - bottom*dir) / (h*dir*dir)) * h*dir
** r*r = radius^2
** so we obtain quadratic equation for t:
** 
*/

/* R(t) = P0 + td
** x1 = bottom, x2 = top
** |(R(t)-x1) X (R(t)-x2)|^2 / |(x1-x2)|^2 = r^2
**
** 0 <= (P-x1)(x2-x1) <= (x2-x1)(x2-x1)
*/

/*
static t_vec pre_compute_coef(t_vec v1, t_vec v2)
{
	return (v_sub(v1, v_mul(v2, v_dot(v1, v2))));
}
*/

int is_cylinder_range(t_cylinder *cy, t_ray ray, double t)
{
	t_vec aa = v_sub(ray_at(ray, t), cy->bottom);
	double aaa = v_dot(aa, cy->direction);
	return (0 <= aaa && aaa <= cy->height);
}

int	hit_cylinder(t_cylinder *cy, t_ray ray, double tmax, t_rec *rec)
{
#if 0
	t_vec	oc;
	t_vec	aa;
	t_vec	bb;
	double	a;
	double	b;
	double	c;
	double	t;

	oc = v_sub(ray.origin, cy->bottom);
	aa = pre_compute_coef(ray.direction, cy->direction);
	bb = pre_compute_coef(oc, cy->direction);
	a = v_dot(aa, aa);
	b = 2 * v_dot(aa, bb);
	c = v_dot(oc, oc) - cy->radius * cy->radius;
#endif
	t_vec BT = v_sub(cy->top, cy->bottom);
	t_vec A = v_sub(v_cross(ray.origin, BT), v_cross(cy->bottom, BT));
	t_vec B = v_cross(ray.direction, BT);
	double root1, root2, t;
	t_coef coef;
	coef.a = v_len_squared(B);
	coef.b = 2 * v_dot(A, B);
	coef.c = v_len_squared(A) - cy->radius * cy->radius * cy->height * cy->height;
	if (quadratic_solve2(&root1, &root2, coef) == 0)
		return (0);
	t_vec aa; double aaa;
	if (EPSILON < root1 && is_cylinder_range(cy, ray, root1))
		t = root1;
	else if (EPSILON < root2 && is_cylinder_range(cy, ray, root2))
		t = root2;
	else
		return (0);
	if (EPSILON <= t && t < tmax)
	{
		rec->color = cy->color;
		rec->t = root1;
		aa = v_sub(ray_at(ray, root1), cy->bottom);
		aaa = v_dot(aa, cy->direction);
//		t_vec res = v_sub(aa, v_mul(cy->direction, v_dot(aa, cy->direction)));
		t_vec res = v_sub(aa, v_mul(cy->direction, aaa));
		if (t == root1)
			rec->normal = v_unit(res);
		else
			rec->normal = v_mul(v_unit(res), -1);
		rec->point = ray_at(ray, t);
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
	if (obj.type == TYPE_CYLINDER)
		return (hit_cylinder(obj.data, ray, tmax, rec));
	return (0);
}

void move_object(t_mlx *rt, double dx, double dy)
{
	t_objects obj;

	obj = rt->objects_array[rt->obj_selected_idx];
	if (obj.type == TYPE_SPHERE)
		move_sphere(obj.data, dx, dy);
	if (obj.type == TYPE_PLANE)
		move_plane(obj.data, dx, dy);
	if (obj.type == TYPE_TRIANGLE)
		move_triangle(obj.data, dx, dy);
	if (obj.type == TYPE_SQUARE)
		move_square(obj.data, dx, dy);
	if (obj.type == TYPE_CYLINDER)
		move_cylinder(obj.data, dx, dy);
}

void resize_object(t_mlx *rt, double amount)
{
	t_objects obj;

	obj = rt->objects_array[rt->obj_selected_idx];
	if (obj.type == TYPE_SPHERE)
		resize_sphere(obj.data, amount);
	if (obj.type == TYPE_SQUARE)
		resize_square(obj.data, amount);
	if (obj.type == TYPE_CYLINDER)
		resize_cylinder(obj.data, amount);
}

void rotate_object(t_mlx *rt, double dx, double dy)
{
	t_objects obj;

	obj = rt->objects_array[rt->obj_selected_idx];
	if (obj.type == TYPE_PLANE)
		rotate_plane(obj.data, dx, dy);
	if (obj.type == TYPE_SQUARE)
		rotate_square(obj.data, dx, dy);
	if (obj.type == TYPE_CYLINDER)
		rotate_cylinder(obj.data, dx, dy);
}

void show_object_info(int idx, t_mlx *rt)
{
	t_cam	*cam;
	char	*msg[10];
	int		i;
	char	*tmp;

	tmp = ft_itoa(idx);
	msg[0] = ft_strjoin("object selected idx:", tmp);
//	if (rt->objects_array[idx].type == TYPE_SPHERE)
//		get_sphere_info(msg, rt->objects_array[idx].data);
//	else
		msg[1] = NULL;
	cam = rt->cam_list->content;
	mlx_put_image_to_window(rt->mlx, rt->win, cam->image.img_ptr, 0, 0);
	i = -1;
	while (msg[++i] != NULL)
	{
		mlx_string_put(rt->mlx, rt->win, 11, 20 * i + 21, 0, msg[i]);
		mlx_string_put(rt->mlx, rt->win, 10, 20 * i + 20,
			255 << 16 | 255 << 8 | 255, msg[i]);
	}
	free(tmp);
	free(msg[0]);
}	
