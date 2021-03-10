/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 11:31:23 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/10 18:08:37 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include "camera.h"
#include "math_utils.h"

t_cam	*new_camera(t_vec origin, t_vec direction, double fov)
{
	t_cam *cam;

	if (!(cam = malloc(sizeof(t_cam))))
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

void	modify_fov(t_cam *cam, double delta)
{
	cam->fov = clamp(cam->fov + delta, 0, 180);
	return ;
}
