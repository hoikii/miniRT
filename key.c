/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 13:02:14 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/09 15:58:21 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key.h"
#include "transform.h"
#include "exit.h"

static void	key_wasd_pressed(int keycode, t_mlx *param)
{
	if (param->object_mode)
	{
		return ;
	}
	else
	{
		if (keycode == KEY_A)
			move_x(param, MV_DEC);
		else if (keycode == KEY_D)
			move_x(param, MV_INC);
		else if (keycode == KEY_W)
			move_z(param, MV_INC);
		else if (keycode == KEY_S)
			move_z(param, MV_DEC);
	}
	render_scene(param, 0);
}

static void	key_arrow_pressed(int keycode, t_mlx *param)
{
	if (keycode == KEY_LEFT)
		rotate_yaw(param, ROTATE_INC);
	else if (keycode == KEY_RIGHT)
		rotate_yaw(param, ROTATE_DEC);
	else if (keycode == KEY_UP)
		rotate_pitch(param, ROTATE_INC);
	else if (keycode == KEY_DOWN)
		rotate_pitch(param, ROTATE_DEC);
	render_scene(param, 0);
}

static void	key_sign_pressed(int keycode, t_mlx *param)
{
	if (keycode == KEY_PLUS)
		modify_fov(param->cam_list->content, -5.0);
	else if (keycode == KEY_MINUS)
		modify_fov(param->cam_list->content, +5.0);
	render_scene(param, 0);
}

void		show_keycode(int keycode, t_mlx *param)
{
	char	*msg;
	char	*str_keycode;
	t_cam	*cam;

	cam = param->cam_list->content;
	mlx_put_image_to_window(param->mlx, param->win, cam->image.img_ptr, 0, 0);
	str_keycode = ft_itoa(keycode);
	msg = ft_strjoin("keycode = ", str_keycode);
	free(str_keycode);
	mlx_string_put(param->mlx, param->win, 11, 21, 0, msg);
	mlx_string_put(param->mlx, param->win, 10, 20,
			255 << 16 | 255 << 8 | 255, msg);
	free(msg);
}

int			key_pressed(int keycode, t_mlx *param)
{
	if (keycode == KEY_ESC)
		close_window(param);
	else if (keycode == KEY_W || keycode == KEY_A
			|| keycode == KEY_S || keycode == KEY_D)
		key_wasd_pressed(keycode, param);
	else if (keycode == KEY_LEFT || keycode == KEY_RIGHT
			|| keycode == KEY_UP || keycode == KEY_DOWN)
		key_arrow_pressed(keycode, param);
	else if (keycode == KEY_PLUS || keycode == KEY_MINUS)
		key_sign_pressed(keycode, param);
	else if (keycode == KEY_SPACE)
	{
		param->cam_list = param->cam_list->next;
		render_scene(param, 0);
	}
	else if (keycode == KEY_O)
		param->object_mode ^= CAM_OBJ_SWITCH;
	else
		show_keycode(keycode, param);
	return (0);
}
