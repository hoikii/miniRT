/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 15:14:14 by kanlee            #+#    #+#             */
/*   Updated: 2020/12/10 10:07:31 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
