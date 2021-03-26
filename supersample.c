/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supersample.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 14:04:24 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/26 20:35:17 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trace_ray.h"

static t_color	get_sample(t_ray ray, double i, double j, t_mlx *rt)
{
	t_color	sample_color;
	int		samples_per_pixel;

	samples_per_pixel = 4;
	ray.direction = set_ray_direction(ray, i, j, rt);
	sample_color = trace_ray(ray, REFLECTION_DEPTH, rt);
	return (c_mul(sample_color, 1.0 / samples_per_pixel));
}

/*
** Use rotated square for sample pixels to improve Anti-Aliasing quality.
*/

void			supersample(t_ray ray, int i, int j, t_mlx *rt)
{
	t_color	pixel_color;

	pixel_color = color(0, 0, 0);
	pixel_color = c_add(pixel_color, get_sample(ray, i - 0.50, j + 0.25, rt));
	pixel_color = c_add(pixel_color, get_sample(ray, i - 0.25, j - 0.50, rt));
	pixel_color = c_add(pixel_color, get_sample(ray, i + 0.50, j - 0.25, rt));
	pixel_color = c_add(pixel_color, get_sample(ray, i + 0.25, j + 0.50, rt));
	set_pixel_color(rt, i, j, pixel_color);
}
