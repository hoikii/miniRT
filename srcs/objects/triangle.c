/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 22:46:49 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/20 16:44:24 by kanlee           ###   ########.fr       */
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

void		move_triangle(t_triangle *tri, t_vec mv)
{
	tri->p1 = v_add(tri->p1, mv);
	tri->p2 = v_add(tri->p2, mv);
	tri->p3 = v_add(tri->p3, mv);
}
