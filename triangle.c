/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 22:46:49 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/10 00:18:40 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "triangle.h"

#include <stdio.h>

t_triangle	*new_triangle(t_vec p1, t_vec p2, t_vec p3, t_color color)
{
	t_triangle *tri;

	if (!(tri = malloc(sizeof(t_triangle))))
		return (NULL);
	tri->p1 = p1;
	tri->p2 = p2;
	tri->p3 = p3;
	tri->normal = v_unit(v_cross(v_sub(p2, p1), v_sub(p3, p1)));
	tri->color = color;
	return (tri);
}

void		free_triangle(t_triangle *tri)
{
	free(tri);
	return ;
}

void		move_triangle(t_triangle *tri, double dx, double dz)
{
	t_vec add;

	if (dx != 0)
		add = v_new(dx, 0, 0);
	if (dz != 0)
		add = v_new(0, 0, dz);
	tri->p1 = v_add(tri->p1, add);
	tri->p2 = v_add(tri->p2, add);
	tri->p3 = v_add(tri->p3, add);

/*
	if (dx != 0)
	{
		tri->p1 = v_add(tri->p1, v_mul(v_new(1, 0, 0), dx));
		tri->p2 = v_add(tri->p2, v_mul(v_new(1, 0, 0), dx));
		tri->p3 = v_add(tri->p3, v_mul(v_new(1, 0, 0), dx));
	}
	else if (dz != 0)
	{
		tri->p1 = v_add(tri->p1, v_mul(v_new(0, 0, 1), dz));
		tri->p2 = v_add(tri->p2, v_mul(v_new(0, 0, 1), dz));
		tri->p3 = v_add(tri->p3, v_mul(v_new(0, 0, 1), dz));
	}
//	tri->normal = v_unit(v_cross(v_sub(tri->p2, tri->p1), v_sub(tri->p3, tri->p1)));
*/
}
