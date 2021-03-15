/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 22:46:55 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/15 15:52:22 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "cylinder.h"
#include "math_utils.h"

void		fill_cylinder_info(t_cylinder *cy, int rotate)
{
	cy->bottom = v_sub(cy->center, v_mul(cy->direction, cy->height / 2));
	cy->top = v_add(cy->center, v_mul(cy->direction, cy->height / 2));
	if (!rotate)
	{
		cy->anglex = rtod(asin(cy->direction.y));
		cy->angley = 0 - rtod(atan2(cy->direction.x, cy->direction.z));
	}
}

void		move_cylinder(t_cylinder *cy, double dx, double dy, double dz)
{
	if (dx != 0)
		cy->center = v_add(cy->center, v_new(dx, 0, 0));
	if (dy != 0)
		cy->center = v_add(cy->center, v_new(0, dy, 0));
	if (dz != 0)
		cy->center = v_add(cy->center, v_new(0, 0, dz));
	fill_cylinder_info(cy, 0);
}

void		resize_cylinder(t_cylinder *cy, double amount, int flag)
{
	if (flag == 0)
		cy->radius += amount;
	else if (flag == 1)
		cy->height += amount;
	fill_cylinder_info(cy, 0);
}

void		rotate_cylinder(t_cylinder *cy, double dx, double dy)
{
	cy->anglex = remainder(cy->anglex + dx + 360, 360);
	cy->angley = remainder(cy->angley + dy + 360, 360);
	cy->direction = v_rotate_x(v_new(0, 0, 1), degree_to_radian(cy->anglex));
	cy->direction = v_rotate_y(cy->direction, degree_to_radian(cy->angley));
	cy->direction = v_unit(cy->direction);
	fill_cylinder_info(cy, 1);
}
