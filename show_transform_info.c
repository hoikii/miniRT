/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_transform_info.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 23:22:10 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/15 23:33:32 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "show_transform_info.h"
#include "objects.h"
#include "light.h"

char		*g_obj_type_string[5] = {
	"Sphere",
	"Plane",
	"Triangle",
	"Square",
	"Cylinder"};

static void	show_object_info(int idx, t_mlx *rt)
{
	t_cam	*cam;
	char	*msg[3];
	int		i;
	char	*idxstring;

	idxstring = ft_itoa(idx);
	msg[0] = ft_strjoin("object selected idx:", idxstring);
	msg[1] = g_obj_type_string[rt->objects_array[idx].type];
	msg[2] = NULL;
	cam = rt->cam_list->content;
	mlx_put_image_to_window(rt->mlx, rt->win, cam->image.img_ptr, 0, 0);
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
	t_cam	*cam;
	char	*msg[3];
	int		i;
	char	*idxstring;

	idxstring = ft_itoa(idx);
	msg[0] = ft_strjoin("light selected idx:", idxstring);
	msg[1] = NULL;
	cam = rt->cam_list->content;
	mlx_put_image_to_window(rt->mlx, rt->win, cam->image.img_ptr, 0, 0);
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
