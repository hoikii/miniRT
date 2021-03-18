/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 14:22:01 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/18 09:00:01 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "minirt.h"
#include "parser_utils.h"
#include "parse_value.h"
#include "parse_objects.h"
#include "color.h"
#include "vec.h"
#include "libft/libft.h"
#include "gnl/get_next_line.h"
#include "camera.h"
#include "light.h"
#include "exit.h"

static void	limit_resolution(int *x, int *y, t_mlx *rt)
{
	int	max_x;
	int	max_y;

	mlx_get_screen_size(rt->mlx, &max_x, &max_y);
	if (*x > max_x || *y > max_y || *x < MIN_X || *y < MIN_Y)
	{
		if (*x > max_x)
			*x = max_x;
		if (*x < MIN_X)
			*x = MIN_X;
		if (*y > max_y)
			*y = max_y;
		if (*y < MIN_Y)
			*y = MIN_Y;
		printf("Limit resolution to %dx%d\n", *x, *y);
	}
}

void		parse_resolution(char *line, t_mlx *rt, int linenum)
{
	int		res_x;
	int		res_y;
	char	**words;

	if (rt->resolution_declared)
		exit_error_ln("Resolution must be declared once.", rt, linenum);
	rt->resolution_declared = 1;
	if (ft_cntwords(line, ' ') != 3)
		exit_error_ln("Resolution: R x y", rt, linenum);
	words = ft_split(line, ' ');
	if ((get_integer(words[1], &res_x) == FAIL) || res_x < 0
		|| (get_integer(words[2], &res_y) == FAIL) || res_y < 0)
		exit_error_ln("Resolution: Invalid integer value", rt, linenum);
	free_words(words);
	limit_resolution(&res_x, &res_y, rt);
	rt->screen_width = res_x;
	rt->screen_height = res_y;
	return ;
}

void		parse_ambient(char *line, t_mlx *rt, int linenum)
{
	char	**words;

	if (rt->ambient_declared)
		exit_error_ln("Ambient must be declared once.", rt, linenum);
	rt->ambient_declared = 1;
	if (ft_cntwords(line, ' ') != 3)
		exit_error_ln("Ambient: A ratio R,G,B", rt, linenum);
	words = ft_split(line, ' ');
	if (get_double(words[1], &rt->ambient.brightness) == FAIL
		|| rt->ambient.brightness < 0 || rt->ambient.brightness > 1)
		exit_error_ln("Ambient ratio must be in range [0.0, 1.0]", rt, linenum);
	if (get_color(words[2], &rt->ambient.color) == FAIL)
		exit_error_ln("Ambient: Invalid color value", rt, linenum);
	free_words(words);
	return ;
}

void		parse_camera(char *line, t_mlx *rt, int linenum)
{
	t_vec	pos;
	t_vec	direction;
	int		fov;
	t_cam	*cam;
	char	**words;

	if (ft_cntwords(line, ' ') != 4)
		exit_error_ln("Camera: c position direction FOV", rt, linenum);
	words = ft_split(line, ' ');
	if (get_vector(words[1], &pos) == FAIL)
		exit_error_ln("Camera: Invalid position vector", rt, linenum);
	if (get_vector_norm(words[2], &direction) == FAIL)
		exit_error_ln("Camera: Direction vector must be in range [-1,1] for \
			each x,y,z", rt, linenum);
	if ((get_integer(words[3], &fov) == FAIL) || fov < 0 || fov > 180)
		exit_error_ln("Camera FOV must be in range [0, 180]", rt, linenum);
	cam = new_camera(pos, direction, fov);
	if (!cam)
		exit_error("Memory allocation failed.", rt);
	cam->image.img_ptr = NULL;
	ft_lstadd_back(&(rt->cam_list), ft_lstnew(cam, 0));
	free_words(words);
}

void		parse_light(char *line, t_mlx *rt, int linenum)
{
	t_vec	pos;
	double	brightness;
	t_color	color;
	t_light	*light;
	char	**words;

	if (ft_cntwords(line, ' ') != 4)
		exit_error_ln("Light: l position ratio R,G,B", rt, linenum);
	words = ft_split(line, ' ');
	if (get_vector(words[1], &pos) == FAIL)
		exit_error_ln("Light: Invalid position vector", rt, linenum);
	if (get_double(words[2], &brightness) == FAIL
		|| brightness < 0.0 || brightness > 1.0)
		exit_error_ln("Light: ratio must be in range [0.0, 1.0]", rt, linenum);
	if (get_color(words[3], &color) == FAIL)
		exit_error_ln("Light: Invalid color value", rt, linenum);
	light = new_light(pos, brightness, color);
	if (!light)
		exit_error("Memory allocation failed.", rt);
	ft_lstadd_back(&(rt->lights_list), ft_lstnew(light, 0));
	free_words(words);
	return ;
}
