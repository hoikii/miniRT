/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 11:31:23 by kanlee            #+#    #+#             */
/*   Updated: 2020/12/07 23:56:35 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include "camera.h"
#include "math_utils.h"
#include <stdio.h>

t_cam *new_camera(t_vec origin, t_vec direction, double fov)
{
	t_cam *cam = malloc(sizeof(t_cam));
	cam->origin = origin;
	cam->direction = v_unit(direction);
	cam->fov = fov;
	cam->vup = v_new(0,1,0);
	cam->tanx = rtod(atan(cam->direction.x / cam->direction.z));
	cam->tany = rtod(asin(cam->direction.y));

	cam->u = v_unit(v_cross(cam->vup, cam->direction));
	cam->v = v_cross(cam->direction, cam->u);
	return cam;
}

void move_camera(t_cam *cam, double dx, double dy)
{
	if (dx != 0)
		cam->origin = v_add(cam->origin, v_mul(cam->u, dx));
	if (dy != 0)
		cam->origin = v_add(cam->origin, v_mul(cam->direction, dy));
}

void rotate_camera(t_cam *cam, double rx, double ry)
{
	if (rx != 0) {
		cam->tanx += rx;
		if (cam->tanx > 360)
			cam->tanx -= 360;
		else if (cam->tanx < 0)
			cam->tanx += 360;
	}
	if (ry != 0)
	{
		cam->tany += ry;
		if (cam->tany > 360)
			cam->tany -= 360;
		else if (cam->tany < 0)
			cam->tany += 360;
	}

	cam->direction = rotateY(v_new(0,0,1), 0 - degree_to_radian(cam->tany));
	cam->direction = rotateX(cam->direction, 0 - degree_to_radian(cam->tanx));
	cam->direction = v_unit(cam->direction);
	cam->vup = rotateY(v_new(0,1,0), 0 - degree_to_radian(cam->tany));
	cam->vup = rotateX(cam->vup, 0 - degree_to_radian(cam->tanx));
	cam->vup = v_unit(cam->vup);
	cam->u = v_unit(v_cross(cam->vup, cam->direction));
	cam->v = v_cross(cam->direction, cam->u);
}

		
void modify_fov(t_cam *cam, double delta)
{
	cam->fov = clamp(cam->fov + delta, 0, 180);
	return ;
}

