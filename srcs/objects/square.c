/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 22:36:01 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/31 00:00:55 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "square.h"
#include "math_utils.h"

void		fill_square_info(t_square *sq, int is_init)
{
	t_vec	center;
	t_vec	right;
	t_vec	normal;
	t_vec	up;

	normal = sq->normal;
	center = sq->center;
	if (is_init)
	{
		sq->up = v_new(0, 1, 0);
		if (normal.x == 0 && normal.z == 0)
			sq->up = v_new(0, 0, -1);
		sq->up = v_unit(v_cross(normal, sq->up));
	}
	up = v_mul(sq->up, sq->size / 2);
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
	if (sq->size + amount > 0 + EPSILON)
	{
		sq->size += amount;
		fill_square_info(sq, 0);
	}
}

void		rotate_square(t_square *sq, t_vec axis, double angle)
{
	sq->normal = v_rotate(sq->normal, axis, angle);
	sq->up = v_rotate(sq->up, axis, angle);
	fill_square_info(sq, 0);
}
