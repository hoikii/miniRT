/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 22:46:55 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/10 18:10:11 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
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
/*
t_cylinder	*new_cylinder(t_vec center, t_vec direction, double diameter, double height, t_color color)
{
	t_cylinder	*cy;

	if (!(cy = malloc(sizeof(t_cylinder))))
		return (NULL);
	cy->center = center;
	cy->direction = v_unit(direction);
	cy->radius = diameter / 2;
	cy->height = height;
	cy->color = color;
	fill_cylinder_info(cy, 0);

	return (cy);
}

void		free_cylinder(t_cylinder *cy)
{
	free(cy);
	return ;
}
*/
void	move_cylinder(t_cylinder *cy, double dx, double dz)
{
	if (dx != 0)
		cy->center = v_add(cy->center, v_mul(v_new(1, 0, 0), dx));
	if (dz != 0)
		cy->center = v_add(cy->center, v_mul(v_new(0, 0, 1), dz));
	fill_cylinder_info(cy, 0);
}

void		resize_cylinder(t_cylinder *cy, double amount)
{
	cy->radius += amount;
	cy->height += amount;
	fill_cylinder_info(cy, 0);
}

void	rotate_cylinder(t_cylinder *cy, double dx, double dy)
{
	cy->anglex = remainder(cy->anglex + dx + 360, 360);
	cy->angley = remainder(cy->angley + dy + 360, 360);
	cy->direction = v_rotate_x(v_new(0, 0, 1), degree_to_radian(cy->anglex));
	cy->direction = v_rotate_y(cy->direction, degree_to_radian(cy->angley));
	cy->direction = v_unit(cy->direction);
	fill_cylinder_info(cy, 1);
}
