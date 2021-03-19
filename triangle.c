/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 22:46:49 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/19 14:35:43 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "triangle.h"

t_triangle	new_triangle(t_vec p1, t_vec p2, t_vec p3, t_color color)
{
	t_triangle	tri;
	t_vec		normal;

	tri.p1 = p1;
	tri.p2 = p2;
	tri.p3 = p3;
	tri.color = color;
	normal = v_cross(v_sub(p2, p1), v_sub(p3, p1));
	tri.normal = v_unit(normal);
	return (tri);
}

void		move_triangle(t_triangle *tri, double dx, double dy, double dz)
{
	t_vec	add;

	if (dx != 0)
		add = v_new(dx, 0, 0);
	if (dy != 0)
		add = v_new(0, dy, 0);
	if (dz != 0)
		add = v_new(0, 0, dz);
	tri->p1 = v_add(tri->p1, add);
	tri->p2 = v_add(tri->p2, add);
	tri->p3 = v_add(tri->p3, add);
}
