/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 14:22:01 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/28 06:19:08 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "minirt.h"
#include "parser_utils.h"
#include "parse_info.h"
#include "parse_objects.h"
#include "parse_value.h"
#include "color.h"
#include "vec.h"
#include "libft/libft.h"
#include "gnl/get_next_line.h"
#include "camera.h"
#include "light.h"
#include "exit.h"

static void	parse_objects(char *line, t_mlx *rt, int linenum)
{
	if (*line == 's' && *(line + 1) == 'p' && *(line + 2) == ' ')
		parse_sphere(line, rt, linenum);
	else if (*line == 'p' && *(line + 1) == 'l' && *(line + 2) == ' ')
		parse_plane(line, rt, linenum);
	else if (*line == 't' && *(line + 1) == 'r' && *(line + 2) == ' ')
		parse_triangle(line, rt, linenum);
	else if (*line == 's' && *(line + 1) == 'q' && *(line + 2) == ' ')
		parse_square(line, rt, linenum);
	else if (*line == 'c' && *(line + 1) == 'y' && *(line + 2) == ' ')
		parse_cylinder(line, rt, linenum);
	else if (*line == 'c' && *(line + 1) == 'c' && *(line + 2) == ' ')
		parse_cylinder_caps(line, rt, linenum);
	else if (*line == 'c' && *(line + 1) == 'u' && *(line + 2) == ' ')
		parse_cube(line, rt, linenum);
	else if (*line == 'p' && *(line + 1) == 'y' && *(line + 2) == ' ')
		parse_pyramid(line, rt, linenum);
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
	else if (BONUS && *line == 'S' && *(line + 1) == 'k' && *(line + 2) == ' ')
		parse_skybox(line, rt, linenum);
	else
		parse_objects(line, rt, linenum);
	return ;
}

static void	light_list_to_array(t_mlx *rt, t_list *lst)
{
	int	i;

	rt->lights_cnt = ft_lstsize(lst);
	rt->lights_array = malloc(sizeof(t_light) * rt->lights_cnt);
	if (!rt->lights_array)
		exit_error("Memory Allocation Failed.", rt);
	i = -1;
	while (++i < rt->lights_cnt)
	{
		rt->lights_array[i] = *(t_light *)(lst->content);
		lst = lst->next;
	}
	return ;
}

static void	check_mandatory(t_mlx *rt)
{
	t_list	*cam_list;
	t_cam	*cam;

	if (rt->resolution_declared == 0)
		exit_error("No Resolution.", rt);
	if (rt->ambient_declared == 0)
		exit_error("No Ambient.", rt);
	if (ft_lstsize(rt->cam_list) == 0)
		exit_error("No Camera", rt);
	cam_list = rt->cam_list;
	while (cam_list)
	{
		cam = cam_list->content;
		cam->image.img_ptr = mlx_new_image(rt->mlx,
				rt->screen_width, rt->screen_height);
		cam->image.imgdata = mlx_get_data_addr(cam->image.img_ptr,
				&cam->image.bpp, &cam->image.size_line, &cam->image.endian);
		cam_list = cam_list->next;
	}
	ft_lstadd_back(&(rt->cam_list), rt->cam_list);
	light_list_to_array(rt, rt->lights_list);
	printf("Rendering %d objects with %d cameras in %dx%d\n",
		rt->objs_cnt, ft_lstsize(rt->cam_list), rt->screen_width,
		rt->screen_height);
	return ;
}

void		parser(char *filepath, t_mlx *rt)
{
	int		fd;
	char	*line;
	int		linenum;

	linenum = 0;
	fd = open(filepath, O_RDWR);
	if (fd < 0)
	{
		if (errno == EISDIR)
			exit_error(ft_strjoin(filepath, " is directory"), rt);
		fd = open(filepath, O_RDONLY);
	}
	if (fd < 0)
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
	close(fd);
	return ;
}
