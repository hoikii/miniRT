/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 22:36:01 by kanlee            #+#    #+#             */
/*   Updated: 2020/12/20 22:30:02 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "square.h"

t_square	*new_square(t_vec center, t_vec normal, double size, t_color color)
{
	t_square	*sq;
	t_vec		up;
	t_vec		right;

	if (!(sq = malloc(sizeof(t_square))))
		return (NULL);
	sq->center = center;
	sq->normal = v_unit(normal);
	sq->size = size;
	sq->color = color;
	if (sq->normal.y != 1)
		up = v_cross(v_new(0,1,0), sq->normal);
	else
		up = v_cross(v_new(normal.x, normal.y, normal.z + 0.001), sq->normal);
	up = v_mul(v_unit(up), size / 2);
	right = v_cross(up, sq->normal);
	right = v_mul(v_unit(right), size / 2);
	sq->p1 = v_add(v_sub(center, up), right);
	sq->p2 = v_add(v_add(center, up), right);
	sq->p3 = v_sub(v_add(center, up), right);
	sq->p4 = v_sub(v_sub(center, up), right);
	return (sq);
}

void		free_square(t_square *sq)
{
	free(sq);
	return ;
}
