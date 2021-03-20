/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 22:36:01 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/21 02:41:09 by kanlee           ###   ########.fr       */
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

void			fill_cube_info(t_cube *cu, int is_init)
{
	t_vec	normal;
	t_vec	up;
	t_vec	right;

	normal = cu->normal;
	if (is_init)
	{
		cu->up = v_new(0, 1, 0);
		if (normal.x == 0 && normal.z == 0)
			cu->up = v_new(0, 0, -1);
	}
	up = cu->up;
	right = v_unit(v_cross(up, normal));
	cu->face[0] = fill_cube_face_info(cu, normal, up, right);
	cu->face[1] = fill_cube_face_info(cu, v_mul(normal, -1), right, up);
	cu->face[2] = fill_cube_face_info(cu, up, right, normal);
	cu->face[3] = fill_cube_face_info(cu, v_mul(up, -1), normal, right);
	cu->face[4] = fill_cube_face_info(cu, right, normal, up);
	cu->face[5] = fill_cube_face_info(cu, v_mul(right, -1), up, normal);
}

void			move_cube(t_cube *cu, t_vec mv)
{
	cu->center = v_add(cu->center, mv);
	fill_cube_info(cu, 0);
}

void			resize_cube(t_cube *cu, double amount)
{
	cu->size += amount;
	fill_cube_info(cu, 0);
}

void			rotate_cube(t_cube *cu, t_vec axis, double angle)
{
	cu->normal = v_rotate(cu->normal, axis, angle);
	cu->up = v_rotate(cu->up, axis, angle);
	fill_cube_info(cu, 0);
}
