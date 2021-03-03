/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 13:02:14 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/03 00:44:25 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key.h"
#include "exit.h"

int key_pressed(int keycode, t_mlx *param) {
	printf("\rkeycode=%d      ", keycode);
	if (keycode == KEY_ESC) {
		close_window(param);
		return 0;
	}
	if (keycode == KEY_A) {
		move_camera(param->cam_list->content, -0.2, 0);
	}
	else if (keycode == KEY_D) {
		move_camera(param->cam_list->content, +0.2, 0);
	}
	else if (keycode == KEY_W) {
		move_camera(param->cam_list->content, 0, +0.2);
	}
	else if (keycode == KEY_S) {
		move_camera(param->cam_list->content, 0, -0.2);
	}
	else if (keycode == KEY_LEFT) {
		rotate_camera(param->cam_list->content, -10, 0);
	}
	else if (keycode == KEY_RIGHT) {
		rotate_camera(param->cam_list->content, +10, 0);
	}
	else if (keycode == KEY_UP) {
		rotate_camera(param->cam_list->content, 0, +10);
	}
	else if (keycode == KEY_DOWN) {
		rotate_camera(param->cam_list->content, 0, -10);
	}
	else if (keycode == KEY_PLUS) {
		modify_fov(param->cam_list->content, -5.0);
	}
	else if (keycode == KEY_MINUS) {
		modify_fov(param->cam_list->content, +5.0);
	}
	else if (keycode == KEY_SPACE)
	{
			param->cam_list = param->cam_list->next;
	}
	render_scene(param, 0);
	return 0;
}

