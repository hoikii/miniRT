/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disruption.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 14:44:24 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/25 00:00:01 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "minirt.h"
#include "objects.h"
#include "color.h"

#define BLACK {0,0,0}
#define WHITE {1,1,1}

t_color	rainbow(t_rec rec)
{
	t_color	local_color;
	t_vec	n;
	double	t;

	if (rec.objtype == TYPE_SPHERE)
		n = v_mul(v_add(rec.normal, v_new(1, 1, 1)), 0.5);
	else if (rec.objtype == TYPE_PLANE)
		n = v_mul(v_add(rec.point, v_new(1, 1, 1)), 0.5);
	else
		n = v_mul(v_add(rec.normal, v_new(1, 1, 1)), 0.5);
	t = fabs(v_dot(rec.normal, rec.raydir));
	local_color = (t_color){n.x, 1 - n.y, n.z};
//	local_color.r = t * cos + (1 - t) * n.x;
//	local_color.g = t * cos + (1 - t) * n.y;
//	local_color.b = t * cos + (1 - t) * n.z;
	return (local_color);
}

t_color	checkerboard(t_rec rec, t_mlx *rt)
{
	t_color	local_color;
	t_vec	tmp;

	local_color = (t_color)BLACK;
	if (rec.objtype == TYPE_SPHERE)
	{
		tmp.x = (int)(fabs(floor(rec.normal.x * 2 ))) % 2;
		tmp.y = (int)(fabs(floor(rec.normal.y * 2 ))) % 2;
		tmp.z = (int)(fabs(floor(rec.normal.z * 2 ))) % 2;
		if ((int)tmp.x ^ (int)tmp.y ^ (int)tmp.z)
			local_color = (t_color)WHITE;
//		double sines = sin( 2*PI * rec.normal.x) * sin( 2*PI *rec.normal.y) * sin( 2*PI *rec.normal.z);
//		if (sines < 0)
//			local_color = (t_color){1,1,1};
	}
	else if (rec.objtype == TYPE_PLANE)
	{
		tmp.x = (int)(fabs(floor(rec.point.x * 2 ))) % 2;
		tmp.y = (int)(fabs(floor(rec.point.y * 2 ))) % 2;
		tmp.z = (int)(fabs(floor(rec.point.z * 2 ))) % 2;
		if ((int)tmp.x ^ (int)tmp.y ^ (int)tmp.z)
			local_color = (t_color)WHITE;
	}
	else if (rec.objtype == TYPE_SQUARE)
	{
		t_square *sq = (t_square *)rt->objects_array[rec.obj_id].data;

		t_vec up = sq->up;
//		t_vec up = v_mul(sq->up, sq->size / 2);
		t_vec right = v_cross(up, sq->normal);
//		right = v_mul(v_unit(right), sq->size / 2);

		tmp.x = (int)(fabs(floor(v_dot(v_sub(rec.point, sq->p1), right) *4/sq->size ))) % 2;
		tmp.y = (int)(fabs(floor(v_dot(v_sub(rec.point, sq->p1), up) *4 / sq->size ))) % 2;
		if ((int)tmp.x ^ (int)tmp.y)
			local_color = (t_color)WHITE;
	}
	return (local_color);
}
