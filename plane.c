/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 15:14:14 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/10 00:36:56 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "plane.h"

t_plane	*new_plane(t_vec point, t_vec normal, t_color color)
{
	t_plane *pl;

	if (!(pl = malloc(sizeof(t_plane))))
		return (NULL);
	pl->point = point;
	pl->normal = v_unit(normal);
	pl->color = color;
	return (pl);
}

void	free_plane(t_plane *pl)
{
	free(pl);
	return ;
}

void	move_plane(t_plane *pl, double dx, double dz)
{
	if (dx != 0)
		pl->point = v_add(pl->point, v_new(dx, 0, 0));
	if (dz != 0)
		pl->point = v_add(pl->point, v_new(0, 0, dz));
}

