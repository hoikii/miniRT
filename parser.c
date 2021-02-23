/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 14:22:01 by kanlee            #+#    #+#             */
/*   Updated: 2021/02/23 13:48:16 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include "minirt.h"
#include "error.h"
#include "parser_utils.h"
#include "parse_value.h"
#include "parse_objects.h"
#include "color.h"
#include "vec.h"
#include "libft/libft.h"
#include "gnl/get_next_line.h"
#include "libft/libft.h"
#include "camera.h"
#include "light.h"
#include "exit.h"

static int parse_resolution(char *line, t_mlx *rt)
{
	int res_x;
	int res_y;

	if (rt->resolution_declared)
		exit_error("Resolution must be declared once.", rt);
	rt->resolution_declared = 1;
	if (ft_cntwords(line, ' ') != 3)
		exit_error("error while parsing resolution\n", rt);
	line++;
	skip_blank(&line);
	rt->screen_width = get_integer(&line);
	skip_blank(&line);
	rt->screen_height = get_integer(&line);
	mlx_get_screen_size(rt->mlx, &res_x, &res_y);
	if (rt->screen_width > res_x || rt->screen_height > res_y)
	{
		printf("Limit resolution to %dx%d\n", res_x, res_y);
		rt->screen_width = res_x;
		rt->screen_height = res_y;
	}
	return SUCCESS;
}

static void parse_ambient(char *line, t_mlx *rt)
{
	if (rt->ambient_declared)
		exit_error("Ambient must be declared once.", rt);
	rt->ambient_declared = 1;
	if (ft_cntwords(line, ' ') != 3)
		exit_error("error while parsing ambient\n", rt);
	line++;
	skip_blank(&line);
	rt->ambient.brightness = get_double(&line);
	skip_blank(&line);
	rt->ambient.color = get_color(&line);
	return ;
}

static void parse_light(char *line, t_mlx *rt)
{
	t_vec pos;
	double brightness;
	t_color color;
	t_light *light;
	
	if (ft_cntwords(line, ' ') != 4)
		exit_error("error while parsing light\n", rt);
	line++;
	skip_blank(&line);
	pos = get_vector(&line);
	skip_blank(&line);
	brightness = get_double(&line);
	skip_blank(&line);
	color = get_color(&line);
	if (!(light = new_light(pos, brightness, color)))
		exit_error("Load failed when parsing light.", rt);
	ft_lstadd_back(&(rt->lights_list), ft_lstnew(light, 0));
	return ;
}

static void parse_camera(char *line, t_mlx *rt)
{
	t_vec pos;
	t_vec direction;
	int fov;
	t_cam *cam;
	char **words;

	if (ft_cntwords(line, ' ') != 4)
		exit_error("error while parsing camera\n", rt);
	words = ft_split(line, ' ');
	pos = get_vector(words[1]);
	direction = get_vector(words[2]);
	fov = get_integer(words[3]);
	if (!(cam = new_camera(pos, direction, fov)))
		exit_error("Load failed when parsing camera.", rt);
	cam->image.img = mlx_new_image(rt->mlx, rt->screen_width, rt->screen_height);
	cam->image.imgdata = mlx_get_data_addr(cam->image.img,
			&cam->image.bpp, &cam->image.size_line, &cam->image.endian);
	ft_lstadd_back(&(rt->cam_list), ft_lstnew(cam, 0));
	return ;
}


static void parse_objects(char *line, t_mlx *rt)
{
	if (*line == 's' && *(line + 1) == 'p')
		parse_sphere(line, rt);
	if (*line == 'p' && *(line + 1) == 'l')
		parse_plane(line, rt);
	if (*line == 't' && *(line + 1) == 'r')
		parse_triangle(line, rt);
	if (*line == 's' && *(line + 1) == 'q')
		parse_square(line, rt);
	if (*line == 'c' && *(line + 1) == 'y')
		parse_cylinder(line, rt);
	return ;
}


static int parse_line(char *line, t_mlx *rt)
{
	int ret = -1;

	skip_blank(&line);
	if (*line == 'R')
		ret = parse_resolution(line, rt);
	else if (*line == 'A')
		parse_ambient(line, rt);
	else if (*line == 'c' && *(line + 1) != 'y')
		parse_camera(line, rt);
	else if (*line == 'l')
		parse_light(line, rt);
	else
		parse_objects(line, rt);
	free(line);
	return ret;
}

void check_parsed(t_mlx *rt)
{
	if (rt->resolution_declared == 0)
		exit_error("Resolution must be declared once.", rt);
	if (rt->ambient_declared == 0)
		exit_error("Ambient must be declared once.", rt);
	if (ft_lstsize(rt->cam_list) == 0)
		exit_error("At least one Camera must be present.", rt);
	ft_lstadd_back(&(rt->cam_list), rt->cam_list);
	return ;
}
int parser(char *filepath, t_mlx *rt)
{
	int		fd;
	char	*line;
	int		parse_error;

	parse_error = SUCCESS;
	if ((fd = open(filepath, O_RDONLY)) < 0)
		return (FILE_OPEN_FAILED);
	while (get_next_line(fd, &line) > 0)
	{
		parse_error = parse_line(line, rt);
		if (parse_error == FAIL)
			break ;
	}
	if (parse_error != FAIL)
		parse_error = parse_line(line, rt);
	if (parse_error != FAIL)
	{
		check_parsed(rt);
		printf("R:%dx%d\n", rt->screen_width, rt->screen_height);
		printf("Cam:%d\n", ft_lstsize(rt->cam_list));
		printf("objs_cnt:%d\n",rt->objs_cnt);
	}
	close(fd);
	return (SUCCESS);
}


