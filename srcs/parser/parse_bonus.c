/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 16:22:04 by kanlee            #+#    #+#             */
/*   Updated: 2021/04/06 18:07:01 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "parse_value.h"
#include "parser_utils.h"
#include "../libft/libft.h"
#include "vec.h"
#include "color.h"
#include "exit.h"

/*
** minilibx for linux cannot load png images :(
*/

#ifdef LINUX

int			get_texture(char *filepath, t_img *texture, t_mlx *rt)
{
	texture->img_ptr = 0;
	if (ft_strncmp(filepath + ft_strlen(filepath) - 3, "xpm", 3) == 0)
		texture->img_ptr = mlx_xpm_file_to_image(rt->mlx, filepath,
				&texture->width, &texture->height);
	if (!(texture->img_ptr))
		return (FAIL);
	texture->imgdata = mlx_get_data_addr(texture->img_ptr,
			&texture->bpp, &texture->size_line, &texture->endian);
	mlx_destroy_image(rt->mlx, texture->img_ptr);
	return (SUCCESS);
}

#else

int			get_texture(char *filepath, t_img *texture, t_mlx *rt)
{
	texture->img_ptr = 0;
	if (ft_strncmp(filepath + ft_strlen(filepath) - 3, "png", 3) == 0)
		texture->img_ptr = mlx_png_file_to_image(rt->mlx, filepath,
				&texture->width, &texture->height);
	else if (ft_strncmp(filepath + ft_strlen(filepath) - 3, "xpm", 3) == 0)
		texture->img_ptr = mlx_xpm_file_to_image(rt->mlx, filepath,
				&texture->width, &texture->height);
	if (!(texture->img_ptr))
		return (FAIL);
	texture->imgdata = mlx_get_data_addr(texture->img_ptr,
			&texture->bpp, &texture->size_line, &texture->endian);
	mlx_destroy_image(rt->mlx, texture->img_ptr);
	return (SUCCESS);
}

#endif

static int	get_bonus_type(char *str, int *ret)
{
	if (ft_strequ(str, "rainbow"))
		*ret = TEXTURE_RAINBOW;
	else if (ft_strequ(str, "checkerboard"))
		*ret = TEXTURE_CHECKERBOARD;
	else if (ft_strequ(str, "wave"))
		*ret = TEXTURE_WAVE;
	else if (ft_strncmp(str, "uvmap:", 6) == 0)
		*ret = TEXTURE_UVMAP;
	else if (ft_strncmp(str, "R:", 2) != 0)
		return (FAIL);
	return (SUCCESS);
}

int			get_bonus(char **str, t_bonus_attr *bonus, int type, t_mlx *rt)
{
	int	i;

	bonus->texture_type = TEXTURE_NONE;
	bonus->refl_rate = 0;
	i = -1;
	while (str[++i] != NULL)
	{
		if (get_bonus_type(str[i], &bonus->texture_type) == FAIL)
			return (FAIL);
		if (ft_strncmp(str[i], "uvmap:", 6) == 0)
		{
			if (type != TYPE_SPHERE)
				return (FAIL);
			if (get_texture(str[i] + 6, &bonus->texture, rt) == FAIL)
				return (FAIL);
		}
		if (ft_strncmp(str[i], "R:", 2) == 0)
		{
			if (get_double(str[i] + 2, &bonus->refl_rate) == FAIL)
				return (FAIL);
			if (bonus->refl_rate < 0.0 || bonus->refl_rate > 1.0)
				return (FAIL);
		}
	}
	return (SUCCESS);
}

void		parse_skybox(char *line, t_mlx *rt, int linenum)
{
	char	**words;

	if (rt->skybox_declared)
		exit_error_ln("Skybox must be declared once.", rt, linenum);
	if (ft_cntwords(line, ' ') != 2)
		exit_error_ln("Skybox: Sk path_to_texture", rt, linenum);
	words = ft_split(line, ' ');
	if (get_texture(words[1], &rt->skybox, rt) == FAIL)
		exit_error_ln("Skybox: Loading texture failed.", rt, linenum);
	rt->skybox_declared = 1;
	free_words(words);
	return ;
}
