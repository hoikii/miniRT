/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 22:46:55 by kanlee            #+#    #+#             */
/*   Updated: 2020/12/23 00:11:16 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "cylinder.h"

t_cylinder	*new_cylinder(t_vec center, t_vec direction, double diameter, double height, t_color color)
{
	t_cylinder	*cy;
	t_vec		bottom;
	t_vec		top;

	if (!(cy = malloc(sizeof(t_cylinder))))
		return (NULL);
	cy->center = center;
	cy->direction = v_unit(direction);
	cy->radius = diameter / 2;
	cy->height = height;
	cy->color = color;
	cy->bottom = v_sub(center, v_mul(cy->direction, height / 2));
	cy->top = v_add(center, v_mul(cy->direction, height / 2));

	return (cy);
}

void		free_cylinder(t_cylinder *cy)
{
	free(cy);
	return ;
}
