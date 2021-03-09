/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 22:36:01 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/10 00:20:30 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "square.h"

void		fill_square_info(t_square *sq)
{
	t_vec center;
	t_vec up;
	t_vec right;
	t_vec normal;

	normal = sq->normal;
	center = sq->center;
	if (normal.y != 1)
		up = v_cross(v_new(0,1,0), normal);
	else
		up = v_cross(v_new(normal.x, normal.y, normal.z + 0.001), normal);
	up = v_mul(v_unit(up), sq->size / 2);
	right = v_cross(up, normal);
	right = v_mul(v_unit(right), sq->size / 2);
	sq->p1 = v_add(v_sub(center, up), right);
	sq->p2 = v_add(v_add(center, up), right);
	sq->p3 = v_sub(v_add(center, up), right);
	sq->p4 = v_sub(v_sub(center, up), right);
}

t_square	*new_square(t_vec center, t_vec normal, double size, t_color color)
{
	t_square	*sq;

	if (!(sq = malloc(sizeof(t_square))))
		return (NULL);
	sq->center = center;
	sq->normal = v_unit(normal);
	sq->size = size;
	sq->color = color;
	fill_square_info(sq);
	return (sq);
}

void		free_square(t_square *sq)
{
	free(sq);
	return ;
}

void	move_square(t_square *sq, double dx, double dz)
{
	if (dx != 0)
		sq->center = v_add(sq->center, v_new(dx, 0, 0));
	if (dz != 0)
		sq->center = v_add(sq->center, v_new(0, 0, dz));
	fill_square_info(sq);
}

void	resize_square(t_square *sq, double amount)
{
	sq->size += amount;
	fill_square_info(sq);
}
