/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 16:22:04 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/28 05:23:04 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_utils.h"
#include "libft/libft.h"
#include "vec.h"
#include "color.h"
#include "exit.h"

int		get_texture(char *filepath, t_img *texture, t_mlx *rt)
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
	return (SUCCESS);
}

int		get_bonus(char *str, int *ret)
{
	*ret = TEXTURE_NONE;
	if (ft_strequ(str, "rainbow"))
		*ret = TEXTURE_RAINBOW;
	else if (ft_strequ(str, "checkerboard"))
		*ret = TEXTURE_CHECKERBOARD;
	else if (ft_strequ(str, "wave"))
		*ret = TEXTURE_WAVE;
	else if (ft_strncmp(str, "uvmap:", 6) == 0)
		*ret = TEXTURE_UVMAP;
	else
		return (FAIL);
	return (SUCCESS);
}

void	parse_skybox(char *line, t_mlx *rt, int linenum)
{
	char	**words;

	if (rt->skybox_declared)
		exit_error_ln("Skybox must be declared once.", rt, linenum);
	rt->skybox_declared = 1;
	if (ft_cntwords(line, ' ') != 2)
		exit_error_ln("Skybox: Sk path_to_texture", rt, linenum);
	words = ft_split(line, ' ');
	if (get_texture(words[1], &rt->skybox, rt) == FAIL)
		exit_error_ln("Skybox: Loading texture failed.", rt, linenum);
	free_words(words);
	return ;
}
