/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pyramid.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 22:36:01 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/31 00:02:58 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "pyramid.h"
#include "math_utils.h"

static void	fill_pyramid_face(t_pyramid *py)
{
	py->face[0] = new_triangle(py->p1, py->p2, py->top, py->color);
	py->face[1] = new_triangle(py->p2, py->p3, py->top, py->color);
	py->face[2] = new_triangle(py->p3, py->p4, py->top, py->color);
	py->face[3] = new_triangle(py->p4, py->p1, py->top, py->color);
	py->face[4] = new_triangle(py->p1, py->p2, py->p3, py->color);
	py->face[5] = new_triangle(py->p3, py->p4, py->p1, py->color);
}

void		fill_pyramid_info(t_pyramid *py, int is_init)
{
	t_vec	center;
	t_vec	up;
	t_vec	right;
	t_vec	normal;

	normal = py->normal;
	center = py->center;
	if (is_init)
	{
		py->up = v_new(0, 1, 0);
		if (normal.x == 0 && normal.z == 0)
			py->up = v_new(0, 0, -1);
		py->up = v_unit(v_cross(normal, py->up));
	}
	up = v_mul(py->up, py->size / 2);
	right = v_cross(up, normal);
	right = v_mul(v_unit(right), py->size / 2);
	py->p1 = v_add(v_sub(center, up), right);
	py->p2 = v_add(v_add(center, up), right);
	py->p3 = v_sub(v_add(center, up), right);
	py->p4 = v_sub(v_sub(center, up), right);
	py->top = v_add(center, v_mul(normal, py->height));
	fill_pyramid_face(py);
}

void		move_pyramid(t_pyramid *py, t_vec mv)
{
	py->center = v_add(py->center, mv);
	fill_pyramid_info(py, 0);
}

void		resize_pyramid(t_pyramid *py, double amount, int flag)
{
	if (flag == 0 && py->size + amount > 0 + EPSILON)
		py->size += amount;
	if (flag == 1 && py->height + amount > 0 + EPSILON)
		py->height += amount;
	fill_pyramid_info(py, 0);
}

void		rotate_pyramid(t_pyramid *py, t_vec axis, double angle)
{
	py->normal = v_rotate(py->normal, axis, angle);
	py->up = v_rotate(py->up, axis, angle);
	fill_pyramid_info(py, 0);
}
