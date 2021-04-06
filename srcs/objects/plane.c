/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 15:14:14 by kanlee            #+#    #+#             */
/*   Updated: 2021/04/04 16:59:32 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "plane.h"
#include "math_utils.h"

void	fill_plane_info(t_plane *pl)
{
	if (pl->normal.y != 1)
		pl->u = v_unit(v_cross(v_new(0, 1, 0), pl->normal));
	else
		pl->u = v_unit(v_cross(v_new(0, 0, -1), pl->normal));
	pl->v = v_unit(v_cross(pl->u, pl->normal));
}

void	move_plane(t_plane *pl, t_vec mv)
{
	pl->point = v_add(pl->point, mv);
}

void	rotate_plane(t_plane *pl, t_vec axis, double angle)
{
	pl->normal = v_rotate(pl->normal, axis, angle);
	fill_plane_info(pl);
}
