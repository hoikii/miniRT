/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 13:02:14 by kanlee            #+#    #+#             */
/*   Updated: 2020/12/03 12:56:21 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key.h"

int key_pressed(int keycode, t_mlx *param) {
	printf("\rkeycode=%d", keycode);
	if (keycode == KEY_ESC) {
		close_window(param);
		return 0;
	}
	if (keycode == KEY_A)
		param->cam.offsetX -= 0.2;
	else if (keycode == KEY_D)
		param->cam.offsetX += 0.2;
	else if (keycode == KEY_W)
		param->cam.offsetZ += 0.2;
	else if (keycode == KEY_S)
		param->cam.offsetZ -= 0.2;
	else if (keycode == KEY_LEFT) {
		param->cam.rotateX += 10;
		param->cam.tanx += 10;
		if (param->cam.tanx > 360)
			param->cam.tanx -= 360;
	}
	else if (keycode == KEY_RIGHT) {
		param->cam.rotateX -= 10;
		param->cam.tanx -= 10;
		if (param->cam.tanx < 0)
			param->cam.tanx += 360;
	}
	else if (keycode == KEY_UP) {
		param->cam.rotateY -= 10;
		param->cam.tany -= 10;
		if (param->cam.tany < 0)
			param->cam.tany += 360;
	}
	else if (keycode == KEY_DOWN) {
		param->cam.rotateY += 10;
		param->cam.tany += 10;
		if (param->cam.tany > 360)
			param->cam.tany -= 360;
	}
	else if (keycode == KEY_PLUS)
		param->cam.fov += 5.0;
	else if (keycode == KEY_MINUS)
		param->cam.fov -= 5.0;
	draw(param);
	return 0;
}

