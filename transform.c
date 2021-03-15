/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 03:56:59 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/15 23:06:55 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "transform.h"
#include "math_utils.h"
#include "camera.h"
#include "objects.h"
#include "light.h"
#include <stdio.h>

void	move(t_mlx *rt, double dx, double dy, double dz)
{
	t_cam	*cam;

	cam = rt->cam_list->content;
	if (rt->transform_mode == MODE_CAM)
		move_camera(cam, dx, dy, dz);
	else if (rt->transform_mode == MODE_OBJ)
		move_object(rt, dx, dy, dz);
	else if (rt->transform_mode == MODE_LIGHT)
		move_light(rt, dx, dy, dz);
	return ;
}

void	rotate_yaw(t_mlx *rt, int amount)
{
	t_cam	*cam;

	cam = rt->cam_list->content;
	if (rt->transform_mode == MODE_CAM)
		rotate_camera(cam, 0, amount);
	else
		rotate_object(rt, 0, amount);
	return ;
}

void	rotate_pitch(t_mlx *rt, int amount)
{
	t_cam	*cam;

	cam = rt->cam_list->content;
	if (rt->transform_mode == MODE_CAM)
		rotate_camera(cam, amount, 0);
	else
		rotate_object(rt, amount, 0);
	return ;
}
