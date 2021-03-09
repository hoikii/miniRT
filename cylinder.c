/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 22:46:55 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/09 22:47:09 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "cylinder.h"

void		fill_cylinder_info(t_cylinder *cy)
{
	cy->bottom = v_sub(cy->center, v_mul(cy->direction, cy->height / 2));
	cy->top = v_add(cy->center, v_mul(cy->direction, cy->height / 2));
}

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
	fill_cylinder_info(cy);

	return (cy);
}

void		free_cylinder(t_cylinder *cy)
{
	free(cy);
	return ;
}

void	move_cylinder(t_cylinder *cy, double dx, double dz)
{
	if (dx != 0)
		cy->center = v_add(cy->center, v_mul(v_new(1, 0, 0), dx));
	if (dz != 0)
		cy->center = v_add(cy->center, v_mul(v_new(0, 0, 1), dz));
	fill_cylinder_info(cy);
}

void		resize_cylinder(t_cylinder *cy, double amount)
{
	cy->radius += amount;
	cy->height += amount;
	fill_cylinder_info(cy);
}
