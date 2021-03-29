/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 11:31:23 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/29 18:19:28 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include "camera.h"
#include "math_utils.h"

t_cam		*new_camera(t_vec origin, t_vec direction, double fov)
{
	t_cam	*cam;
	t_vec	tmp;

	cam = malloc(sizeof(t_cam));
	if (!cam)
		return (NULL);
	cam->origin = origin;
	cam->direction = direction;
	cam->fov = fov;
	tmp = v_new(0, 1, 0);
	if (cam->direction.x == 0 && cam->direction.z == 0)
		tmp = v_new(0, 0, -1);
	cam->u = v_unit(v_cross(tmp, cam->direction));
	cam->v = v_unit(v_cross(cam->direction, cam->u));
	return (cam);
}

void		move_camera(t_cam *cam, t_vec mv)
{
	cam->origin = v_add(cam->origin, mv);
}

void		rotate_camera_yaw(t_cam *cam, double angle)
{
	cam->v = v_rotate(cam->v, v_new(0, 1, 0), angle);
	cam->u = v_rotate(cam->u, v_new(0, 1, 0), angle);
	cam->direction = v_unit(v_cross(cam->u, cam->v));
}

void		rotate_camera_pitch(t_cam *cam, double angle)
{
	cam->v = v_rotate(cam->v, cam->u, angle);
	cam->direction = v_unit(v_cross(cam->u, cam->v));
}

void		modify_fov(t_cam *cam, double delta)
{
	cam->fov = clamp(cam->fov + delta, 0, 180);
	return ;
}
