/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 14:22:01 by kanlee            #+#    #+#             */
/*   Updated: 2020/12/05 18:17:52 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include "minirt.h"
#include "error.h"
#include "parser_utils.h"
#include "parse_value.h"
#include "parse_objects.h"
#include "color.h"
#include "vec.h"
#include "libft/libft.h"
#include "gnl/get_next_line.h"
#include <stdio.h>


static void parse_resolution(char *line, t_mlx *rt)
{
	line++;
	skip_blank(&line);
	rt->screen_width = get_integer(&line);
	skip_blank(&line);
	rt->screen_height = get_integer(&line);
	return ;
}

static void parse_ambient(char *line, t_mlx *rt)
{
	double amb;
	t_color color;

	line++;
	skip_blank(&line);
	amb = get_double(&line);
	skip_blank(&line);
	color = get_color(&line);
	return ;
}

static void parse_camera(char *line, t_mlx *rt)
{
	t_vec pos;
	t_vec direction;
	int fov;

	line++;
	skip_blank(&line);
	pos = get_vector(&line);
	skip_blank(&line);
	direction = get_vector(&line);
	skip_blank(&line);
	fov = get_integer(&line);
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

	return ;
}


static void parse_line(char *line, t_mlx *rt)
{
	skip_blank(&line);
	if (*line == 'R')
		parse_resolution(line, rt);
	else if (*line == 'A')
		parse_ambient(line, rt);
	else if (*line == 'c')
		parse_camera(line, rt);
	else
		parse_objects(line, rt);
	return ;
}

int parser(char *filepath, t_mlx *rt)
{
	int fd;
	char *line;

	if ((fd = open(filepath, O_RDONLY)) < 0)
		return (FILE_OPEN_FAILED);
	while (get_next_line(fd, &line) > 0)
	{
		parse_line(line, rt);
		free(line);
	}
	parse_line(line, rt);
	free(line);

	printf("R:%dx%d\n", rt->screen_width, rt->screen_height);
	printf("objs_cnt:%d\n",rt->objs_cnt);
	close(fd);
	return (SUCCESS);
}


