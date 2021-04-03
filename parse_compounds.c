/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_compounds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 16:48:20 by kanlee            #+#    #+#             */
/*   Updated: 2021/04/03 18:36:06 by kanlee           ###   ########.fr       */
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

void	parse_cylinder_caps(char *line, t_mlx *rt, int linenum)
{
	t_cylinder	*cy;
	char		**words;

	if (ft_cntwords(line, ' ') < 6)
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
	if (BONUS && get_bonus(words + 6, &cy->bonus, rt) == FAIL)
		exit_error_ln("Cylinder: Invalid Bonus type", rt, linenum);
	fill_cylinder_info(cy);
	set_wave_attr(&cy->bonus, 50, 0.05);
	append_object(cy, TYPE_CYLINDER_CAPS, rt);
	free_words(words);
	return ;
}

void	parse_cube(char *line, t_mlx *rt, int linenum)
{
	t_cube	*cu;
	char	**words;

	if (ft_cntwords(line, ' ') < 5)
		exit_error_ln("Cube: cu center normal  size R,G,B", rt, linenum);
	cu = malloc(sizeof(t_cube));
	if (!cu)
		exit_error("Memory allocation failed.", rt);
	words = ft_split(line, ' ');
	if (get_vector(words[1], &cu->center) == FAIL
		|| get_double(words[3], &cu->size) == FAIL
		|| get_color(words[4], &cu->color) == FAIL)
		exit_error_ln("Cube: Invalid parameters", rt, linenum);
	if (get_vector_norm(words[2], &cu->normal) == FAIL)
		exit_error_ln("Cube: Direction vector must be in range [-1,1] for \
			each x,y,z", rt, linenum);
	if (BONUS && get_bonus(words + 5, &cu->bonus, rt) == FAIL)
		exit_error_ln("Cube: Invalid Bonus type", rt, linenum);
	fill_cube_info(cu, 1);
	set_wave_attr(&cu->bonus, 50, 0.05);
	append_object(cu, TYPE_CUBE, rt);
	free_words(words);
	return ;
}

void	parse_pyramid(char *line, t_mlx *rt, int linenum)
{
	t_pyramid	*py;
	char		**words;

	if (ft_cntwords(line, ' ') < 6)
		exit_error_ln("Pyramid: py center norm size height R,G,B", rt, linenum);
	py = malloc(sizeof(t_pyramid));
	if (!py)
		exit_error("Memory allocation failed.", rt);
	words = ft_split(line, ' ');
	if (get_vector(words[1], &py->center) == FAIL
		|| get_double(words[3], &py->size) == FAIL
		|| get_double(words[4], &py->height) == FAIL
		|| get_color(words[5], &py->color) == FAIL)
		exit_error_ln("Pyramid: Invalid parameters", rt, linenum);
	if (get_vector_norm(words[2], &py->normal) == FAIL)
		exit_error_ln("Pyramid: Direction vector must be in range [-1,1] for \
			each x,y,z", rt, linenum);
	if (BONUS && get_bonus(words + 6, &py->bonus, rt) == FAIL)
		exit_error_ln("Pyramid: Invalid Bonus type", rt, linenum);
	fill_pyramid_info(py, 1);
	set_wave_attr(&py->bonus, 50, 0.05);
	append_object(py, TYPE_PYRAMID, rt);
	free_words(words);
	return ;
}
