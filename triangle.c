/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 22:46:49 by kanlee            #+#    #+#             */
/*   Updated: 2020/12/10 09:50:18 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "triangle.h"

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
