/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supersample.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 14:04:24 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/26 19:03:46 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trace_ray.h"

static t_color sample_color(t_ray ray, double i, double j, t_mlx *rt)
{
	t_color ret;

	ray.direction = set_ray_direction(ray, i, j, rt);
	return (c_mul(trace_ray(ray, REFLECTION_DEPTH, rt), 0.25));
}

void	supersample(t_ray ray, int i, int j, t_mlx *rt)
{
#if 0
	t_color aa = color(0,0,0);
	aa = c_add(aa, sample_color(ray, vp, (double)i - 0.5, (double)j - 0.5, rt));
	aa = c_add(aa, sample_color(ray, vp, (double)i - 0.5, (double)j + 0.5, rt));
	aa = c_add(aa, sample_color(ray, vp, (double)i + 0.5, (double)j - 0.5, rt));
	aa = c_add(aa, sample_color(ray, vp, (double)i + 0.5, (double)j + 0.5, rt));
	set_pixel_color(rt, i, j, aa);
#endif
#if 0
	t_color aa = color(0,0,0);
	aa = c_add(aa, sample_color(ray, vp, (double)i - 0.5, (double)j + 0.25, rt));
	aa = c_add(aa, sample_color(ray, vp, (double)i + 0.5, (double)j - 0.25, rt));
	aa = c_add(aa, sample_color(ray, vp, (double)i - 0.25, (double)j - 0.5, rt));
	aa = c_add(aa, sample_color(ray, vp, (double)i + 0.25, (double)j + 0.5, rt));
	set_pixel_color(rt, i, j, aa);
#endif
#if 1
	t_color aa = color(0,0,0);
	aa = c_add(aa, sample_color(ray, (double)i - 0.5, (double)j, rt));
	aa = c_add(aa, sample_color(ray, (double)i + 0.5, (double)j, rt));
	aa = c_add(aa, sample_color(ray, (double)i, (double)j - 0.5, rt));
	aa = c_add(aa, sample_color(ray, (double)i, (double)j + 0.5, rt));
	set_pixel_color(rt, i, j, aa);
#endif
}
