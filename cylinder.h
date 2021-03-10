/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 22:49:36 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/10 14:27:08 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CYLINDER_H
# define CYLINDER_H

# include "vec.h"
# include "color.h"

typedef struct	s_cylinder {
	t_vec		center;
	t_vec		direction;
	double		radius;
	double		height;
	t_color		color;
	t_vec		bottom;
	t_vec		top;
	double		anglex;
	double		angley;
}				t_cylinder;

t_cylinder	*new_cylinder(t_vec center, t_vec direction, double diameter, double height, t_color color);
void		free_cylinder(t_cylinder *cy);

void		fill_cylinder_info(t_cylinder *cy, int rotate);
void		move_cylinder(t_cylinder *cy, double dx, double dz);
void		resize_cylinder(t_cylinder *cy, double amount);
void	rotate_cylinder(t_cylinder *cy, double dx, double dy);
#endif
