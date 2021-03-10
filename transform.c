/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 03:56:59 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/10 12:46:57 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "transform.h"
#include "camera.h"
#include "math_utils.h"
#include "objects.h"
#include <stdio.h>

void		move_x(t_mlx *rt, double amount)
{
	t_cam *cam;

	cam = rt->cam_list->content;
	if (rt->transform_mode == MODE_CAM)
		cam->origin = v_add(cam->origin, v_mul(cam->u, amount));
	else
		move_object(rt, amount, 0);
	return ;
}

void		move_z(t_mlx *rt, double amount)
{
	t_cam *cam;

	cam = rt->cam_list->content;
	if (rt->transform_mode == MODE_CAM)
		cam->origin = v_add(cam->origin, v_mul(cam->direction, amount));
	else
		move_object(rt, 0, amount);
	return ;
}

static void	calc_cam_direction(t_cam *cam)
{
	cam->direction = v_rotate_x(v_new(0, 0, 1), degree_to_radian(cam->anglex));
	cam->direction = v_rotate_y(cam->direction, degree_to_radian(cam->angley));
	cam->direction = v_unit(cam->direction);
	cam->vup = v_rotate_x(v_new(0, 1, 0), degree_to_radian(cam->anglex));
	cam->vup = v_rotate_y(cam->vup, degree_to_radian(cam->angley));
	cam->u = v_unit(v_cross(cam->vup, cam->direction));
	cam->v = v_cross(cam->direction, cam->u);
	return ;
}

void		rotate_yaw(t_mlx *rt, int amount)
{
	t_cam *cam;

	cam = rt->cam_list->content;
	if (rt->transform_mode == MODE_CAM)
	{
		cam->angley += amount;
		cam->angley = remainder(cam->angley + 360, 360);
		calc_cam_direction(cam);
	}
	else
		rotate_object(rt, 0, amount);
	return ;
}

void		rotate_pitch(t_mlx *rt, int amount)
{
	t_cam *cam;

	cam = rt->cam_list->content;
	if (rt->transform_mode == MODE_CAM)
	{
		cam->anglex += amount;
		cam->anglex = remainder(cam->anglex + 360, 360);
		calc_cam_direction(cam);
	}
	else
		rotate_object(rt, amount, 0);
	return ;
}
