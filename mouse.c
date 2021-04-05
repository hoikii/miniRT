/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 21:13:51 by kanlee            #+#    #+#             */
/*   Updated: 2021/04/05 19:38:51 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mouse.h"
#include "camera.h"
#include "math_utils.h"

int	mouse_clicked(int btn, int click_x, int click_y, t_mlx *rt)
{
	t_vec	direction;
	t_cam	*cam;
	double	x;
	double	y;
	t_vec	tmp;

	if (!BONUS ||  btn != MOUSE_LCLICK || click_y <= 0)
		return (0);
	cam = (t_cam *)(rt->cam_list->content);
	x = (double)click_x / (rt->screen_width - 1);
	y = (double)click_y / (rt->screen_height - 1);
	direction = v_add(cam->vp.upper_left_corner, v_mul(cam->vp.horizontal, x));
	direction = v_add(direction, v_mul(cam->vp.vertical, y));
	direction = v_sub(direction, cam->origin);
	cam->direction = v_unit(direction);
	tmp = v_new(0, 1, 0);
	if (cam->direction.x == 0 && cam->direction.z == 0)
		tmp = v_new(0, 0, -1);
	cam->u = v_unit(v_cross(tmp, cam->direction));
	cam->v = v_unit(v_cross(cam->direction, cam->u));
	render_scene(rt, 0);
	return (0);
}
