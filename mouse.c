/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 21:13:51 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/27 19:09:21 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mouse.h"
#include "camera.h"
#include "math_utils.h"

int	mouse_clicked(int btn, int click_x, int click_y, t_mlx *rt)
{
printf("btn=%d   (%d,%d)\n", btn, click_x, click_y);
	t_vec	direction;
	t_cam	*cam;
	double	x;
	double	y;

	if (btn != MOUSE_LCLICK || click_y <= 0)
		return (0);
	cam = (t_cam *)(rt->cam_list->content);
	x = (double)click_x / (rt->screen_width - 1);
	y = (double)click_y / (rt->screen_height - 1);
	direction = v_add(cam->vp.upper_left_corner, v_mul(cam->vp.horizontal, x));
	direction = v_add(direction, v_mul(cam->vp.vertical, y));
	direction = v_sub(direction, cam->origin);
	direction = v_unit(direction);
	cam->anglex = rtod(asin(direction.y));
	cam->angley = 0 - rtod(atan2(direction.x, direction.z));
	rotate_camera(cam, 0, 0);
	render_scene(rt, 0);
	return (0);
}
