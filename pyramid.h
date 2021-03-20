/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pyramid.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 22:39:51 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/20 17:47:48 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PYRAMID_H
# define PYRAMID_H

# include "vec.h"
# include "color.h"
# include "triangle.h"
# include "square.h"

typedef struct	s_pyramid {
	t_vec		center;
	t_vec		normal;
	double		size;
	double		height;
	t_color		color;
	t_square	face_btm;
	t_triangle	face[6];
	t_vec		p1;
	t_vec		p2;
	t_vec		p3;
	t_vec		p4;
	t_vec		top;
	double		anglex;
	double		angley;
}				t_pyramid;

void			fill_pyramid_info(t_pyramid *py, int rotate);
void			move_pyramid(t_pyramid *py, t_vec mv);
void			resize_pyramid(t_pyramid *py, double amount, int flag);
void			rotate_pyramid(t_pyramid *py, double dx, double dy);

#endif
