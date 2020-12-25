/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 16:48:20 by kanlee            #+#    #+#             */
/*   Updated: 2020/12/23 00:16:32 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_objects.h"
#include "parse_value.h"
#include "parser_utils.h"
#include "objects.h"
#include "vec.h"
#include "color.h"
#include "exit.h"

void	parse_sphere(char *line, t_mlx *rt)
{
	t_sphere	*sp;
	t_vec		center;
	double		radius;
	t_color		color;

	line += 2;
	skip_blank(&line);
	center = get_vector(&line);
	skip_blank(&line);
	radius = get_double(&line);
	skip_blank(&line);
	color = get_color(&line);
	if (!(sp = new_sphere(center, radius, color)))
		exit_error("Failed while loading sphere.", rt);
	append_object(sp, TYPE_SPHERE, rt);
	return ;
}

void	parse_plane(char *line, t_mlx *rt)
{
	t_plane	*pl;
	t_vec	point;
	t_vec	normal;
	t_color	color;

	line += 2;
	skip_blank(&line);
	point = get_vector(&line);
	skip_blank(&line);
	normal = get_vector(&line);
	skip_blank(&line);
	color = get_color(&line);
	if (!(pl = new_plane(point, normal, color)))
		exit_error("Failed while loading plane.", rt);
	append_object(pl, TYPE_PLANE, rt);
	return ;
}

void	parse_triangle(char *line, t_mlx *rt)
{
	t_triangle	*tr;
	t_vec		p1;
	t_vec		p2;
	t_vec		p3;
	t_color		color;

	line += 2;
	skip_blank(&line);
	p1 = get_vector(&line);
	skip_blank(&line);
	p2 = get_vector(&line);
	skip_blank(&line);
	p3 = get_vector(&line);
	skip_blank(&line);
	color = get_color(&line);
	if (!(tr = new_triangle(p1, p2, p3, color)))
		exit_error("Failed while loading triangle.", rt);
	append_object(tr, TYPE_TRIANGLE, rt);
	return ;
}

void	parse_square(char *line, t_mlx *rt)
{
	t_square	*sq;
	t_vec		center;
	t_vec		normal;
	double		size;
	t_color		color;

	line += 2;
	skip_blank(&line);
	center = get_vector(&line);
	skip_blank(&line);
	normal = get_vector(&line);
	skip_blank(&line);
	size = get_double(&line);
	skip_blank(&line);
	color = get_color(&line);
	if (!(sq = new_square(center, normal, size, color)))
		exit_error("Failed while loading square.", rt);
	append_object(sq, TYPE_SQUARE, rt);
	return ;
}

void	parse_cylinder(char *line, t_mlx *rt)
{
	t_cylinder	*cy;
	t_vec		center;
	t_vec		direction;
	double		diameter;
	double		height;
	t_color		color;

	line += 2;
	skip_blank(&line);
	center = get_vector(&line);
	skip_blank(&line);
	direction = get_vector(&line);
	skip_blank(&line);
	diameter = get_double(&line);
	skip_blank(&line);
	height = get_double(&line);
	skip_blank(&line);
	color = get_color(&line);
	if (!(cy = new_cylinder(center, direction, diameter, height, color)))
		exit_error("Failed while loading cylinder.", rt);
	append_object(cy, TYPE_CYLINDER, rt);
	return ;
}
