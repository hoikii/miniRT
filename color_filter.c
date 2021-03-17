/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_filter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 13:34:35 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/18 01:57:02 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color_filter.h"
#include "color.h"
#include "math_utils.h"

/*
** RGB to YCbCr
**
**	double y = 0.299 * r + 0.587 * g + 0.114 * b;
**	double cb = -0.16874 * r - 0.33126 * g + 0.50000 * b;
**	double cr = 0.50000 * r - 0.41869 * g - 0.08131 * b;
**	//cb = 0.564(b-y)
**	//cr = 0.713(r-y)
**
**	r = y + 1.40200 * cr;
**	g = y - 0.34414 * cb - 0.71414 * cr;
**	b = y + 1.77200 * cb;
**
**	r = clamp(r, 0, 255);
**	g = clamp(g, 0, 255);
**	b = clamp(b, 0, 255);
**
**	imgfilter[pos + 0] = b;
**	imgfilter[pos + 1] = g;
**	imgfilter[pos + 2] = r;
*/

static int	apply_sepia(int r, int g, int b)
{
	double	grey;

	grey = clamp(r * 0.299 + g * 0.587 + b * 0.114, 0, 255);
	r = clamp(grey * 1.31, 0, 255);
	g = clamp(r * 0.89, 0, 255);
	b = clamp(r * 0.69, 0, 255);
	return (r << 16 | g << 8 | b);
}

static int	apply_sepia2(int r, int g, int b)
{
	double	y;
	double	cb;
	double	cr;

	y = 0.299 * r + 0.587 * g + 0.114 * b;
	cb = -0.16874 * r - 0.33126 * g + 0.50000 * b;
	cr = 0.50000 * r - 0.41869 * g - 0.08131 * b;
	cb = -0.2 * 255;
	cr = 0.1 * 255;
	y = clamp(y, 0, 255);
	cb = clamp(cb, -127.5, 127.5);
	cr = clamp(cr, -127.5, 127.5);
	r = y + 1.40200 * cr;
	g = y - 0.34414 * cb - 0.71414 * cr;
	b = y + 1.77200 * cb;
	r = clamp(r, 0, 255);
	g = clamp(g, 0, 255);
	b = clamp(b, 0, 255);
	return (r << 16 | g << 8 | b);
}

static int	apply_filter(int filter_type, unsigned int color)
{
	int	r;
	int	g;
	int	b;
	int	grey;

	r = color << 8 >> 24;
	g = color << 16 >> 24;
	b = color << 24 >> 24;
	if (filter_type == FILTER_RED)
		return (r << 16 | 0 << 8 | 0);
	if (filter_type == FILTER_GREEN)
		return (0 << 16 | g << 8 | 0);
	if (filter_type == FILTER_BLUE)
		return (0 << 16 | 0 << 8 | b);
	if (filter_type == FILTER_GREY)
	{
		grey = clamp(r * 0.299 + g * 0.587 + b * 0.114, 0, 255);
		return (grey << 16 | grey << 8 | grey);
	}
	if (filter_type == FILTER_SEPIA)
		return (apply_sepia(r, g, b));
	if (filter_type == FILTER_INVERSE)
		return ((255 - r) << 16 | (255 - g) << 8 | (255 - b));
	if (filter_type == FILTER_SEPIA2)
		return (apply_sepia2(r, g, b));
	return (0);
}

void		apply_color_filter(t_mlx *rt)
{
	t_img			image;
	void			*imgptr_filter;
	char			*imgdata_filter;
	int				pos;
	unsigned int	color;

	image = ((t_cam *)(rt->cam_list->content))->image;
	imgptr_filter = mlx_new_image(rt->mlx, rt->screen_width, rt->screen_height);
	imgdata_filter = mlx_get_data_addr(imgptr_filter,
			&image.bpp, &image.size_line, &image.endian);
	pos = (rt->screen_height - 1) * image.size_line
		+ (rt->screen_width - 1) * image.bpp / 8;
	while (pos >= 0)
	{
		pos -= image.bpp / 8;
		if (pos < 0)
			break ;
		color = *(unsigned int *)(&image.imgdata[pos]);
		*(int *)(&imgdata_filter[pos]) = apply_filter(rt->color_filter, color);
	}
	mlx_put_image_to_window(rt->mlx, rt->win, imgptr_filter, 0, 0);
	mlx_destroy_image(rt->mlx, imgptr_filter);
}
