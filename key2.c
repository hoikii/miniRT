/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 17:05:53 by kanlee            #+#    #+#             */
/*   Updated: 2021/04/05 17:07:31 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key.h"
#include "objects.h"
#include "transform.h"
#include "camera.h"
#include "exit.h"
#include "show_transform_info.h"

void	key_wasd(int keycode, t_mlx *rt)
{
	if (keycode == KEY_A)
		move(rt, MV_DEC, 0, 0);
	else if (keycode == KEY_D)
		move(rt, MV_INC, 0, 0);
	else if (keycode == KEY_W)
		move(rt, 0, 0, MV_INC);
	else if (keycode == KEY_S)
		move(rt, 0, 0, MV_DEC);
	if (keycode == KEY_Q)
		move(rt, 0, MV_INC, 0);
	else if (keycode == KEY_Z)
		move(rt, 0, MV_DEC, 0);
	render_scene(rt, 0);
}

void	key_arrow(int keycode, t_mlx *rt)
{
	if (keycode == KEY_LEFT)
		rotate_yaw(rt, ROTATE_INC);
	else if (keycode == KEY_RIGHT)
		rotate_yaw(rt, ROTATE_DEC);
	else if (keycode == KEY_UP)
		rotate_pitch(rt, ROTATE_INC);
	else if (keycode == KEY_DOWN)
		rotate_pitch(rt, ROTATE_DEC);
	render_scene(rt, 0);
}

void	key_sign(int keycode, t_mlx *rt)
{
	if (rt->transform_mode == MODE_CAM)
	{
		if (keycode == KEY_NP_PLUS || keycode == KEY_PLUS)
			modify_fov(rt->cam_list->content, -5.0);
		else if (keycode == KEY_NP_MINUS || keycode == KEY_MINUS)
			modify_fov(rt->cam_list->content, +5.0);
	}
	else if (rt->transform_mode == MODE_OBJ)
	{
		if (keycode == KEY_NP_PLUS || keycode == KEY_PLUS)
			resize_object(rt, 0.1, 0);
		else if (keycode == KEY_NP_MINUS || keycode == KEY_MINUS)
			resize_object(rt, -0.1, 0);
		else if (keycode == KEY_NP_MUL || keycode == KEY_MUL)
			resize_object(rt, 0.1, 1);
		else if (keycode == KEY_NP_DIV || keycode == KEY_DIV)
			resize_object(rt, -0.1, 1);
	}
	render_scene(rt, 0);
}
