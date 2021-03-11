/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 22:46:49 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/11 02:33:28 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "triangle.h"

void	move_triangle(t_triangle *tri, double dx, double dy, double dz)
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
