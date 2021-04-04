/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 22:46:55 by kanlee            #+#    #+#             */
/*   Updated: 2021/04/05 00:06:51 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "cylinder.h"
#include "math_utils.h"

void		fill_cylinder_info(t_cylinder *cy)
{
	cy->radius = cy->diameter / 2.0;
	cy->bottom = v_sub(cy->center, v_mul(cy->direction, cy->height / 2));
	cy->top = v_add(cy->center, v_mul(cy->direction, cy->height / 2));
	if (cy->direction.y != 1)
		cy->meridian = v_unit(v_cross(cy->direction, v_new(0, 1, 0)));
	else
		cy->meridian = v_unit(v_cross(cy->direction, v_new(0, 0, -1)));
}

void		move_cylinder(t_cylinder *cy, t_vec mv)
{
	cy->center = v_add(cy->center, mv);
	fill_cylinder_info(cy);
}

void		resize_cylinder(t_cylinder *cy, double amount, int flag)
{
	if (flag == 0 && cy->diameter + amount > 0 + EPSILON)
		cy->diameter += amount;
	if (flag == 1 && cy->height + amount > 0 + EPSILON)
		cy->height += amount;
	fill_cylinder_info(cy);
}

void		rotate_cylinder(t_cylinder *cy, t_vec axis, double angle)
{
	cy->direction = v_rotate(cy->direction, axis, angle);
	fill_cylinder_info(cy);
}
