/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 11:31:23 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/20 17:34:36 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include "camera.h"
#include "math_utils.h"

t_cam		*new_camera(t_vec origin, t_vec direction, double fov)
{
	t_cam	*cam;

	cam = malloc(sizeof(t_cam));
	if (!cam)
		return (NULL);
	cam->origin = origin;
	cam->direction = direction;
	cam->fov = fov;
	cam->vup = v_new(0, 1, 0);
	if (cam->direction.x == 0 && cam->direction.z == 0)
		cam->vup = v_new(0, 0, -1);
	cam->anglex = rtod(asin(cam->direction.y));
	cam->angley = 0 - rtod(atan2(cam->direction.x, cam->direction.z));
	cam->u = v_unit(v_cross(cam->vup, cam->direction));
	cam->v = v_cross(cam->direction, cam->u);
	return (cam);
}

void		move_camera(t_cam *cam, t_vec mv)
{
	cam->origin = v_add(cam->origin, mv);
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

void		rotate_camera(t_cam *cam, double dx, double dy)
{
	cam->anglex = remainder(cam->anglex + dx + 360, 360);
	cam->angley = remainder(cam->angley + dy + 360, 360);
	calc_cam_direction(cam);
}

void		modify_fov(t_cam *cam, double delta)
{
	cam->fov = clamp(cam->fov + delta, 0, 180);
	return ;
}
