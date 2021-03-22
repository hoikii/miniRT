/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disruption.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 14:44:24 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/23 00:14:29 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "minirt.h"
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
	else
		n = v_mul(v_add(rec.point, v_new(1, 1, 1)), 0.5);
	t = fabs(v_dot(rec.normal, rec.raydir));
	local_color = (t_color){n.x, 1 - n.y, n.z};
//	local_color.r = 0.7 * t + 0.3 * n.x;
//	local_color.g = 0.7 * t + 0.3 * n.y;
//	local_color.b = 0.7 * t + 0.3 * n.z;
	return (local_color);
}

t_color	checkerboard(t_rec rec)
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
	else
	{
		tmp.x = (int)(fabs(floor(rec.point.x * 2 ))) % 2;
		tmp.y = (int)(fabs(floor(rec.point.y * 2 ))) % 2;
		tmp.z = (int)(fabs(floor(rec.point.z * 2 ))) % 2;
		if ((int)tmp.x ^ (int)tmp.y ^ (int)tmp.z)
			local_color = (t_color)WHITE;
/*
		if (v_dot(rec.normal, v_new(0, 0, 1)))
			if ((int)(floor(rec.point.x * 5) + floor(rec.point.y*5)) % 2)
				local_color = (t_color){1,1,1};
		if (v_dot(rec.normal, v_new(1, 0, 0)))
			if ((int)(floor(rec.point.z*5) + floor(rec.point.y*5)) % 2)
				local_color = (t_color){1,1,1};
		if (v_dot(rec.normal, v_new(0, 1, 0)))
			if ((int)(floor(rec.point.x*5) + floor(rec.point.z*5)) % 2)
				local_color = (t_color){1,1,1};
*/
	}
	return (local_color);
}
