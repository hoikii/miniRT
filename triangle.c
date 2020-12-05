/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 22:46:49 by kanlee            #+#    #+#             */
/*   Updated: 2020/11/29 23:14:31 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "triangle.h"

t_triangle *new_triangle(t_vec p1, t_vec p2, t_vec p3, t_color color)
{
	t_triangle *tri = malloc(sizeof(t_triangle));
	tri->p1 = p1;
	tri->p2 = p2;
	tri->p3 = p3;
	tri->normal = v_unit(v_cross(v_sub(p2, p1), v_sub(p3, p1)));
	tri->color = color;
	return tri;
}

void free_triangle(t_triangle *tri)
{
	free(tri);
	return ;
}
