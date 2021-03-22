/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disruption.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 14:44:24 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/22 14:12:42 by kanlee           ###   ########.fr       */
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
	t_vec n = v_mul(v_add(rec.normal, v_new(1, 1, 1)), 0.5);
	double t = 0.7;
	local_color = (t_color){n.x, n.y, n.z};
	return (local_color);
}

t_color	checkerboard(t_rec rec)
{
	t_color	local_color;
		local_color = (t_color)BLACK;
#if 1
		int a = (int)(fabs(floor(rec.normal.x * 2 ))) % 2;
		int b = (int)(fabs(floor(rec.normal.y * 2 ))) % 2;
		int c = (int)(fabs(floor(rec.normal.z * 2 ))) % 2;
		if (a^b^c)
			local_color = (t_color)WHITE;
//		double sines = sin( 2*PI * rec.normal.x) * sin( 2*PI *rec.normal.y) * sin( 2*PI *rec.normal.z);
//		if (sines < 0)
//			local_color = (t_color){1,1,1};
#else
		if (v_dot(rec.normal, v_new(0, 0, 1)))
			if ((int)(floor(rec.point.x * 5) + floor(rec.point.y*5)) % 2)
				local_color = (t_color){1,1,1};
		if (v_dot(rec.normal, v_new(1, 0, 0)))
			if ((int)(floor(rec.point.z*5) + floor(rec.point.y*5)) % 2)
				local_color = (t_color){1,1,1};
		if (v_dot(rec.normal, v_new(0, 1, 0)))
			if ((int)(floor(rec.point.x*5) + floor(rec.point.z*5)) % 2)
				local_color = (t_color){1,1,1};
#endif
		return (local_color);
}
