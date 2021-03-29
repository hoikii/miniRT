/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 16:48:20 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/29 18:30:35 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_objects.h"
#include "parse_value.h"
#include "parser_utils.h"
#include "objects.h"
#include "vec.h"
#include "color.h"
#include "exit.h"
#include "math_utils.h"

void	parse_sphere(char *line, t_mlx *rt, int linenum)
{
	t_sphere	*sp;
	double		diameter;
	char		**words;

	if ((ft_cntwords(line, ' ') != 4) && (ft_cntwords(line, ' ') != 4 + BONUS))
		exit_error_ln("Sphere: sp center diameter R,G,B", rt, linenum);
	sp = malloc(sizeof(t_sphere));
	if (!sp)
		exit_error("Memory allocation failed.", rt);
	words = ft_split(line, ' ');
	if (get_vector(words[1], &sp->center) == FAIL)
		exit_error_ln("Sphere: Invalid coordinates", rt, linenum);
	if (get_double(words[2], &diameter) == FAIL)
		exit_error_ln("Sphere: Invalid diameter value", rt, linenum);
	if (get_color(words[3], &sp->color) == FAIL)
		exit_error_ln("Sphere: Invalid color value", rt, linenum);
	if (BONUS && words[4] != 0 && get_bonus(words[4], &sp->bonus) == FAIL)
		exit_error_ln("Sphere: Invalid Bonus type", rt, linenum);
	if (BONUS && sp->bonus == TEXTURE_UVMAP
		&& get_texture(words[4] + 6, &sp->texture, rt) == FAIL)
		exit_error_ln("Sphere: Loading texture failed", rt, linenum);
	sp->radius = diameter / 2;
	append_object(sp, TYPE_SPHERE, rt);
	free_words(words);
	return ;
}

void	parse_plane(char *line, t_mlx *rt, int linenum)
{
	t_plane	*pl;
	char	**words;

	if ((ft_cntwords(line, ' ') != 4) && (ft_cntwords(line, ' ') != 4 + BONUS))
		exit_error_ln("Plane: pl point normal R,G,B", rt, linenum);
	pl = malloc(sizeof(t_plane));
	if (!pl)
		exit_error("Memory allocation failed.", rt);
	words = ft_split(line, ' ');
	if (get_vector(words[1], &pl->point) == FAIL)
		exit_error_ln("Plane: Invalid coordinates", rt, linenum);
	if (get_vector_norm(words[2], &pl->normal) == FAIL)
		exit_error_ln("Plane: Normal vector must be in range [-1,1] for \
			each x,y,z", rt, linenum);
	if (get_color(words[3], &pl->color) == FAIL)
		exit_error_ln("Plane: Invalid color value", rt, linenum);
	if (BONUS && words[4] != 0 && get_bonus(words[4], &pl->bonus) == FAIL)
		exit_error_ln("Plane: Invalid Bonus type", rt, linenum);
	append_object(pl, TYPE_PLANE, rt);
	free_words(words);
	return ;
}

void	parse_triangle(char *line, t_mlx *rt, int linenum)
{
	t_triangle	*tri;
	t_vec		normal;
	char		**words;

	if ((ft_cntwords(line, ' ') != 5) && (ft_cntwords(line, ' ') != 5 + BONUS))
		exit_error_ln("Triangle: tr point point point color", rt, linenum);
	tri = malloc(sizeof(t_triangle));
	if (!tri)
		exit_error("Memory allocation failed.", rt);
	words = ft_split(line, ' ');
	if (get_vector(words[1], &tri->p1) == FAIL
		|| get_vector(words[2], &tri->p2) == FAIL
		|| get_vector(words[3], &tri->p3) == FAIL)
		exit_error_ln("Triangle: Invalid point value", rt, linenum);
	if (get_color(words[4], &tri->color) == FAIL)
		exit_error_ln("Triangle: Invalid color value", rt, linenum);
	if (BONUS && words[5] != 0 && get_bonus(words[5], &tri->bonus) == FAIL)
		exit_error_ln("Triangle: Invalid Bonus type", rt, linenum);
	normal = v_cross(v_sub(tri->p2, tri->p1), v_sub(tri->p3, tri->p1));
	tri->normal = v_unit(normal);
	append_object(tri, TYPE_TRIANGLE, rt);
	free_words(words);
	return ;
}

void	parse_square(char *line, t_mlx *rt, int linenum)
{
	t_square	*sq;
	char		**words;

	if ((ft_cntwords(line, ' ') != 5) && (ft_cntwords(line, ' ') != 5 + BONUS))
		exit_error_ln("Square: sq center normal  size R,G,B", rt, linenum);
	sq = malloc(sizeof(t_square));
	if (!sq)
		exit_error("Memory allocation failed.", rt);
	words = ft_split(line, ' ');
	if (get_vector(words[1], &sq->center) == FAIL
		|| get_double(words[3], &sq->size) == FAIL
		|| get_color(words[4], &sq->color) == FAIL)
		exit_error_ln("Square: Invalid parameters", rt, linenum);
	if (get_vector_norm(words[2], &sq->normal) == FAIL)
		exit_error_ln("Square: Direction vector must be in range [-1,1] for \
			each x,y,z", rt, linenum);
	if (BONUS && words[5] != 0 && get_bonus(words[5], &sq->bonus) == FAIL)
		exit_error_ln("Square: Invalid Bonus type", rt, linenum);
	fill_square_info(sq, 1);
	append_object(sq, TYPE_SQUARE, rt);
	free_words(words);
	return ;
}

void	parse_cylinder(char *line, t_mlx *rt, int linenum)
{
	t_cylinder	*cy;
	char		**words;

	if ((ft_cntwords(line, ' ') != 6) && (ft_cntwords(line, ' ') != 6 + BONUS))
		exit_error_ln("Cylinder: cy center normal diameter height R,G,B",
			rt, linenum);
	cy = malloc(sizeof(t_cylinder));
	if (!cy)
		exit_error("Memory allocation failed.", rt);
	words = ft_split(line, ' ');
	if (get_vector_norm(words[2], &cy->direction) == FAIL)
		exit_error_ln("Cylinder: Direction vector must be in range [-1,1] for \
			each x,y,z", rt, linenum);
	if ((get_vector(words[1], &cy->center) == FAIL)
		|| (get_double(words[3], &cy->diameter) == FAIL)
		|| (get_double(words[4], &cy->height) == FAIL)
		|| (get_color(words[5], &cy->color) == FAIL))
		exit_error_ln("Cylinder: Invalid parameters", rt, linenum);
	if (BONUS && words[6] != 0 && get_bonus(words[6], &cy->bonus) == FAIL)
		exit_error_ln("Cylinder: Invalid Bonus type", rt, linenum);
	fill_cylinder_info(cy);
	append_object(cy, TYPE_CYLINDER, rt);
	free_words(words);
	return ;
}
