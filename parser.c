/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 14:22:01 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/08 05:10:52 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include "minirt.h"
#include "error.h"
#include "parser_utils.h"
#include "parse_info.h"
#include "parse_objects.h"
#include "parse_value.h"
#include "color.h"
#include "vec.h"
#include "libft/libft.h"
#include "gnl/get_next_line.h"
#include "libft/libft.h"
#include "camera.h"
#include "light.h"
#include "exit.h"

static void	parse_objects(char *line, t_mlx *rt, int linenum)
{
	if (*line == 's' && *(line + 1) == 'p')
		parse_sphere(line, rt, linenum);
	else if (*line == 'p' && *(line + 1) == 'l')
		parse_plane(line, rt, linenum);
	else if (*line == 't' && *(line + 1) == 'r')
		parse_triangle(line, rt, linenum);
	else if (*line == 's' && *(line + 1) == 'q')
		parse_square(line, rt, linenum);
	else if (*line == 'c' && *(line + 1) == 'y')
		parse_cylinder(line, rt, linenum);
	else if (*line != '\0')
		exit_error_ln("Unknown element", rt, linenum);
	return ;
}

static void	parse_line(char *line, t_mlx *rt, int linenum)
{
	skip_blank(&line);
	if (*line == 'R' && *(line + 1) == ' ')
		parse_resolution(line, rt, linenum);
	else if (*line == 'A' && *(line + 1) == ' ')
		parse_ambient(line, rt, linenum);
	else if (*line == 'c' && *(line + 1) == ' ')
		parse_camera(line, rt, linenum);
	else if (*line == 'l' && *(line + 1) == ' ')
		parse_light(line, rt, linenum);
	else
		parse_objects(line, rt, linenum);
	return ;
}

static void	check_mandatory(t_mlx *rt)
{
	if (rt->resolution_declared == 0)
		exit_error("No Resolution.", rt);
	if (rt->ambient_declared == 0)
		exit_error("No Ambient.", rt);
	if (ft_lstsize(rt->cam_list) == 0)
		exit_error("No Camera", rt);
	ft_lstadd_back(&(rt->cam_list), rt->cam_list);
	return ;
}

void		parser(char *filepath, t_mlx *rt)
{
	int		fd;
	char	*line;
	int		linenum;

	linenum = 0;
	if ((fd = open(filepath, O_RDONLY)) < 0)
		exit_error(ft_strjoin("cannot open ", filepath), rt);
	while (get_next_line(fd, &line) > 0)
	{
		linenum++;
		parse_line(line, rt, linenum);
		free(line);
	}
	parse_line(line, rt, linenum);
	free(line);
	check_mandatory(rt);
	printf ("Rendering %d objects with %d cameras in %dx%d\n",
		rt->objs_cnt, ft_lstsize(rt->cam_list), rt->screen_width,
		rt->screen_height);
	close(fd);
	return ;
}
