/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 15:14:14 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/20 16:43:14 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "plane.h"
#include "math_utils.h"

void	move_plane(t_plane *pl, t_vec mv)
{
	pl->point = v_add(pl->point, mv);
}

void	rotate_plane(t_plane *pl, double dx, double dy)
{
	pl->anglex = remainder(pl->anglex + dx + 360, 360);
	pl->angley = remainder(pl->angley + dy + 360, 360);
	pl->normal = v_rotate_x(v_new(0, 0, 1), degree_to_radian(pl->anglex));
	pl->normal = v_rotate_y(pl->normal, degree_to_radian(pl->angley));
	pl->normal = v_unit(pl->normal);
}
