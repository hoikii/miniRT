/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 13:01:49 by kanlee            #+#    #+#             */
/*   Updated: 2020/11/24 11:24:20 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color2.h"

void set_pixel_color(t_mlx *rt, int y, int x,  t_color _color)
{
	char *imgdata = rt->imgdata;
	int color = mlx_get_color_value(rt->mlx, rgb_to_int(_color.r, _color.g, _color.b));
	color = color_to_int(_color);
	int sp = y * rt->size_line + x * rt->bpp / 8;

	imgdata[sp + 0] = color;
	imgdata[sp + 1] = color >> 8;
	imgdata[sp + 2] = color >> 16;
	return ;
}
