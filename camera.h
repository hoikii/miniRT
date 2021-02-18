/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 18:02:21 by kanlee            #+#    #+#             */
/*   Updated: 2020/12/31 00:34:24 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "vec.h"

typedef struct	s_img {
	void		*img;
	char		*imgdata;
	int			bpp;
	int			size_line;
	int			endian;
}				t_img;

typedef struct	s_cam {
	t_vec		origin;
	t_vec		direction;
	double		fov;
	t_vec		vup;
	double		tanx;
	double		tany;
	t_vec		u;
	t_vec		v;
	t_img		image;
}				t_cam;

typedef struct	s_viewport {
	t_vec		horizontal;
	t_vec		vertical;
	t_vec		upper_left_corner;
}				t_viewport;

t_cam			*new_camera(t_vec origin, t_vec direction, double fov);
void			move_camera(t_cam *cam, double dx, double dy);
void			rotate_camera(t_cam *cam, double rx, double ry);
void			modify_fov(t_cam *cam, double delta);

#endif
