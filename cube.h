/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 22:39:51 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/20 16:46:13 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include "vec.h"
# include "color.h"
# include "square.h"

typedef struct	s_cube {
	t_vec		center;
	t_vec		normal;
	double		size;
	t_color		color;
	t_square	face[6];
	double		anglex;
	double		angley;
}				t_cube;

void			fill_cube_info(t_cube *cu, int rotate);
void			move_cube(t_cube *cu, t_vec mv);
void			resize_cube(t_cube *cu, double amount);
void			rotate_cube(t_cube *cu, double dx, double dy);

#endif
