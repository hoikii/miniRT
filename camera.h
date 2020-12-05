/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 18:02:21 by kanlee            #+#    #+#             */
/*   Updated: 2020/11/28 16:47:36 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

typedef struct s_cam {
	t_vec origin;
	t_vec direction;
	double offsetX;
	double offsetZ;
	double fov;
	double rotateX;
	double rotateY;
	t_vec vup;
	double tanx;
	double tany;
} t_cam;

#endif
