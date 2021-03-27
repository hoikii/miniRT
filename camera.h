/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 18:02:21 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/27 19:04:15 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "minirt.h"
# include "vec.h"

typedef struct	s_viewport {
	t_vec		horizontal;
	t_vec		vertical;
	t_vec		upper_left_corner;
}				t_viewport;

typedef struct	s_cam {
	t_vec		origin;
	t_vec		direction;
	double		fov;
	t_vec		vup;
	double		anglex;
	double		angley;
	t_vec		u;
	t_vec		v;
	t_img		image;
	t_viewport	vp;
}				t_cam;

t_cam			*new_camera(t_vec origin, t_vec direction, double fov);
void			move_camera(t_cam *cam, t_vec mv);
void			rotate_camera(t_cam *cam, double dx, double dy);
void			modify_fov(t_cam *cam, double delta);

#endif
