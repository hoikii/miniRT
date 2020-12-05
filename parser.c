/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 14:22:01 by kanlee            #+#    #+#             */
/*   Updated: 2020/12/03 12:48:55 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include "minirt.h"
#include "sphere.h"
#include "plane.h"
#include "triangle.h"
#include "color.h"
#include "vec.h"
#include "libft/libft.h"
#include "gnl/get_next_line.h"
#include <stdio.h>

void skip_blank(char **line)
{
	while (**line && **line == ' ')
		(*line)++;
	return ;
}

void skip_sep(char **line)
{
	skip_blank(line);
	while (**line && **line == ',')
		(*line)++;
	skip_blank(line);
	return ;
}

int get_integer(char **line)
{
	int ret;
	int sign;

	sign = 1;
	if (**line == '-')
		sign = -1;
	if (**line == '-' || **line == '+')
		(*line)++;
	ret = 0;
	while (**line && ft_isdigit(**line))
	{
		ret = ret * 10 + **line - '0';
		(*line)++;
	}
	return (ret * sign);
}

double get_double(char **line)
{
	double ret;
	double decimal;
	int sign;

	sign = 1;
	if (**line == '-')
		sign = -1;
	if (**line == '-' || **line == '+')
		(*line)++;
	ret = get_integer(line);
	decimal = 0.1;
	if (**line == '.')
	{
		(*line)++;
		while (**line && ft_isdigit(**line))
		{
			ret = ret + (**line - '0') * decimal;
			decimal /= 10;
			(*line)++;
		}
	}
	return (ret * sign);
}

t_color get_color(char **line)
{
	t_color ret;

	ret.r = get_integer(line) / 255.0;
	skip_sep(line);
	ret.g = get_integer(line) / 255.0;
	skip_sep(line);
	ret.b = get_integer(line) / 255.0;
	return (ret);
}

t_vec get_vector(char **line)
{
	t_vec ret;

	ret.x = get_double(line);
	skip_sep(line);
	ret.y = get_double(line);
	skip_sep(line);
	ret.z = get_double(line);
	return (ret);
}


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

static void append_object(void *obj, int type, t_mlx *rt)
{
	int cnt;
	int i;
	t_objects new_item;

	new_item.type = type;
	new_item.data = obj;
	cnt = rt->objs_cnt;
	if ((cnt + 1) % 10 == 1)
	{
		t_objects *newarray = malloc((sizeof(t_objects) * (cnt + 10)));
		for (i = 0; i < cnt; i++)
			newarray[i] = rt->objects_array[i];
		if (cnt > 0)
			free(rt->objects_array);
		newarray[i] = new_item;
		rt->objects_array = newarray;
	}
	else
		rt->objects_array[cnt] = new_item;
	(rt->objs_cnt)++;
	return ;
}


static void parse_sphere(char *line, t_mlx *rt)
{
	t_sphere *sp;
	t_vec center;
	double radius;
	t_color color;

	line += 2;
	skip_blank(&line);
	center = get_vector(&line);
	skip_blank(&line);
	radius = get_double(&line);
	skip_blank(&line);
	color = get_color(&line);
	sp = new_sphere(center, radius, color);
	append_object(sp, TYPE_SPHERE, rt);
	return ;
}

static void parse_plane(char *line, t_mlx *rt)
{
	t_plane *pl;
	t_vec point;
	t_vec normal;
	t_color color;

	line += 2;
	skip_blank(&line);
	point = get_vector(&line);
	skip_blank(&line);
	normal = get_vector(&line);
	skip_blank(&line);
	color = get_color(&line);
	pl = new_plane(point, normal, color);
	append_object(pl, TYPE_PLANE, rt);
	return ;
}

static void parse_triangle(char *line, t_mlx *rt)
{
	t_triangle *tr;
	t_vec p1;
	t_vec p2;
	t_vec p3;
	t_color color;

	line += 2;
	skip_blank(&line);
	p1 = get_vector(&line);
	skip_blank(&line);
	p2 = get_vector(&line);
	skip_blank(&line);
	p3 = get_vector(&line);
	color = get_color(&line);
	tr = new_triangle(p1, p2, p3, color);
	append_object(tr, TYPE_TRIANGLE, rt);
	return ;
}

static void parse_objects(char *line, t_mlx *rt)
{
	if (*line == 's' && *(line + 1) == 'p')
		parse_sphere(line, rt);
	if (*line == 'p' && *(line + 1) == 'l')
		parse_plane(line, rt);
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

void parser(t_mlx *rt)
{
	int fd = open("smpl.rt", O_RDONLY);
	int r;
	char *line;

	while ((r = get_next_line(fd, &line) > 0)) {
		parse_line(line, rt);
		free(line);
	}
	ft_putstr_fd(line, 0);
	free(line);

	printf("R:%dx%d\n", rt->screen_width, rt->screen_height);
	printf("objs_cnt:%d\n",rt->objs_cnt);
	return ;
}


