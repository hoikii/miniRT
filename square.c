/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 22:36:01 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/20 16:44:51 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "square.h"
#include "math_utils.h"
#include <stdio.h>

void		fill_square_info(t_square *sq, int rotate)
{
	t_vec	center;
	t_vec	up;
	t_vec	right;
	t_vec	normal;

	normal = sq->normal;
	center = sq->center;
	if (!rotate)
	{
		sq->anglex = rtod(asin(normal.y));
		sq->angley = 0 - rtod(atan2(normal.x, normal.z));
	}
	up = v_rotate_x(v_new(0, 1, 0), degree_to_radian(sq->anglex));
	up = v_rotate_y(up, degree_to_radian(sq->angley));
	up = v_mul(v_unit(up), sq->size / 2);
	right = v_cross(up, normal);
	right = v_mul(v_unit(right), sq->size / 2);
	sq->p1 = v_add(v_sub(center, up), right);
	sq->p2 = v_add(v_add(center, up), right);
	sq->p3 = v_sub(v_add(center, up), right);
	sq->p4 = v_sub(v_sub(center, up), right);
}

void		move_square(t_square *sq, t_vec mv)
{
	sq->center = v_add(sq->center, mv);
	fill_square_info(sq, 0);
}

void		resize_square(t_square *sq, double amount)
{
	sq->size += amount;
	fill_square_info(sq, 0);
}

void		rotate_square(t_square *sq, double dx, double dy)
{
	sq->anglex = remainder(sq->anglex + dx + 360, 360);
	sq->angley = remainder(sq->angley + dy + 360, 360);
	sq->normal = v_rotate_x(v_new(0, 0, 1), degree_to_radian(sq->anglex));
	sq->normal = v_rotate_y(sq->normal, degree_to_radian(sq->angley));
	sq->normal = v_unit(sq->normal);
	fill_square_info(sq, 1);
}
