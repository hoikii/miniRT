/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 22:36:01 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/19 01:38:32 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "cube.h"
#include "math_utils.h"

static t_square	fill_cube_face_info(t_cube *cu, t_vec dir, t_vec u, t_vec v)
{
	t_square	sq;

	sq.normal = dir;
	sq.center = v_add(cu->center, v_mul(dir, cu->size / 2));
	sq.size = cu->size;
	sq.color = cu->color;
	u = v_mul(u, cu->size / 2);
	v = v_mul(v, cu->size / 2);
	sq.p1 = v_add(v_sub(sq.center, u), v);
	sq.p2 = v_add(v_add(sq.center, u), v);
	sq.p3 = v_sub(v_add(sq.center, u), v);
	sq.p4 = v_sub(v_sub(sq.center, u), v);
	return (sq);
}

void			fill_cube_info(t_cube *cu, int rotate)
{
	t_vec	normal;
	t_vec	up;
	t_vec	right;

	normal = cu->normal;
	if (!rotate)
	{
		cu->anglex = rtod(asin(cu->normal.y));
		cu->angley = 0 - rtod(atan2(cu->normal.x, cu->normal.z));
	}
	up = v_rotate_x(v_new(0, 1, 0), degree_to_radian(cu->anglex));
	up = v_rotate_y(up, degree_to_radian(cu->angley));
	up = v_unit(up);
	right = v_unit(v_cross(up, normal));
	cu->face[0] = fill_cube_face_info(cu, normal, up, right);
	cu->face[1] = fill_cube_face_info(cu, v_mul(normal, -1), right, up);
	cu->face[2] = fill_cube_face_info(cu, up, right, normal);
	cu->face[3] = fill_cube_face_info(cu, v_mul(up, -1), normal, right);
	cu->face[4] = fill_cube_face_info(cu, right, normal, up);
	cu->face[5] = fill_cube_face_info(cu, v_mul(right, -1), up, normal);
}

void			move_cube(t_cube *cu, double dx, double dy, double dz)
{
	if (dx != 0)
		cu->center = v_add(cu->center, v_new(dx, 0, 0));
	if (dy != 0)
		cu->center = v_add(cu->center, v_new(0, dy, 0));
	if (dz != 0)
		cu->center = v_add(cu->center, v_new(0, 0, dz));
	fill_cube_info(cu, 0);
}

void			resize_cube(t_cube *cu, double amount)
{
	cu->size += amount;
	fill_cube_info(cu, 0);
}

void			rotate_cube(t_cube *cu, double dx, double dy)
{
	cu->anglex = remainder(cu->anglex + dx + 360, 360);
	cu->angley = remainder(cu->angley + dy + 360, 360);
	cu->normal = v_rotate_x(v_new(0, 0, 1), degree_to_radian(cu->anglex));
	cu->normal = v_rotate_y(cu->normal, degree_to_radian(cu->angley));
	cu->normal = v_unit(cu->normal);
	fill_cube_info(cu, 1);
}
