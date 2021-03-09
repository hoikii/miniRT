/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 16:35:03 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/09 22:52:45 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "sphere.h"

t_sphere	*new_sphere(t_vec center, double radius, t_color color)
{
	t_sphere *sp;

	if (!(sp = malloc(sizeof(t_sphere))))
		return (NULL);
	sp->center = center;
	sp->radius = radius;
	sp->color = color;
	return (sp);
}

void		free_sphere(t_sphere *sp)
{
	free(sp);
	return ;
}

void		move_sphere(t_sphere *sp, double dx, double dz)
{
	if (dx != 0)
		sp->center = v_add(sp->center, v_mul(v_new(1, 0, 0), dx));
	if (dz != 0)
		sp->center = v_add(sp->center, v_mul(v_new(0, 0, 1), dz));
}

void		resize_sphere(t_sphere *sp, double amount)
{
	sp->radius += amount;
}

void		get_sphere_info(char **msg, t_sphere *sp)
{
	msg[1] = "sphere";
	msg[2] = "center";
	msg[3] = "radius";
	msg[4] = "color";
	msg[5] = NULL;
}
