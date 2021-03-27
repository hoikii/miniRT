/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_transform_info.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 23:22:10 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/27 16:35:48 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "show_transform_info.h"
#include "objects.h"
#include "light.h"

const char	*g_obj_type_string[] = {
	"Sphere",
	"Plane",
	"Triangle",
	"Square",
	"Cylinder",
	"Cylinder with caps",
	"Cube",
	"Pyramid"};

void		show_keycode(int keycode, t_mlx *rt)
{
	char	*msg;
	char	*str_keycode;

	put_img_to_window(rt);
	str_keycode = ft_itoa(keycode);
	msg = ft_strjoin("keycode = ", str_keycode);
	free(str_keycode);
	mlx_string_put(rt->mlx, rt->win, 11, 21, 0, msg);
	mlx_string_put(rt->mlx, rt->win, 10, 20,
		255 << 16 | 255 << 8 | 255, msg);
	free(msg);
}

static void	show_object_info(int idx, t_mlx *rt)
{
	char	*msg[3];
	int		i;
	char	*idxstring;

	idxstring = ft_itoa(idx);
	msg[0] = ft_strjoin("object selected idx:", idxstring);
	msg[1] = (char *)g_obj_type_string[rt->objects_array[idx].type];
	msg[2] = NULL;
	i = -1;
	while (msg[++i] != NULL)
	{
		mlx_string_put(rt->mlx, rt->win, 11, 20 * i + 21, 0, msg[i]);
		mlx_string_put(rt->mlx, rt->win, 10, 20 * i + 20,
			255 << 16 | 255 << 8 | 255, msg[i]);
	}
	free(idxstring);
	free(msg[0]);
}

static void	show_light_info(int idx, t_mlx *rt)
{
	char	*msg[3];
	int		i;
	char	*idxstring;

	idxstring = ft_itoa(idx);
	msg[0] = ft_strjoin("light selected idx:", idxstring);
	msg[1] = NULL;
	i = -1;
	while (msg[++i] != NULL)
	{
		mlx_string_put(rt->mlx, rt->win, 11, 20 * i + 21, 0, msg[i]);
		mlx_string_put(rt->mlx, rt->win, 10, 20 * i + 20,
			255 << 16 | 255 << 8 | 255, msg[i]);
	}
	free(idxstring);
	free(msg[0]);
}

void		show_transform_info(int idx, t_mlx *rt)
{
	if (rt->transform_mode == MODE_OBJ)
		show_object_info(idx, rt);
	else if (rt->transform_mode == MODE_LIGHT)
		show_light_info(idx, rt);
	return ;
}
