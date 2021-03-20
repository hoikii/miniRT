/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 15:14:14 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/21 02:52:54 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "plane.h"
#include "math_utils.h"

void	move_plane(t_plane *pl, t_vec mv)
{
	pl->point = v_add(pl->point, mv);
}

void	rotate_plane(t_plane *pl, t_vec axis, double angle)
{
	pl->normal = v_rotate(pl->normal, axis, angle);
}
