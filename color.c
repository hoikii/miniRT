/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 13:01:49 by kanlee            #+#    #+#             */
/*   Updated: 2020/12/07 15:05:09 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "math_utils.h"

t_color color(double r, double g, double b)
{
	t_color c;

	c.r = r;
	c.g = g;
	c.b = b;
	return (c);
}

t_color c_mix(t_color a, t_color b)
{
	a.r = clamp(a.r * b.r, 0, 1);
	a.g = clamp(a.g * b.g, 0, 1);
	a.b = clamp(a.b * b.b, 0, 1);
	return (a);
}

t_color c_add(t_color a, t_color b)
{
	a.r = clamp(a.r + b.r, 0, 1);
	a.g = clamp(a.g + b.g, 0, 1);
	a.b = clamp(a.b + b.b, 0, 1);
	return (a);
}

t_color c_mul(t_color a, double b)
{
	a.r = clamp(a.r * b, 0, 1);
	a.g = clamp(a.g * b, 0, 1);
	a.b = clamp(a.b * b, 0, 1);
	return (a);
}

int rgb_to_int(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

int color_to_int(t_color c)
{
	int r = (int)clamp(c.r * 255, 0, 255);
	int g = (int)clamp(c.g * 255, 0, 255);
	int b = (int)clamp(c.b * 255, 0, 255);
	return (r << 16 | g << 8 | b);
}
