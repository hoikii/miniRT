/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 22:49:36 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/22 18:26:02 by kanlee           ###   ########.fr       */
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
	int			bonus;
}				t_cylinder;

void			fill_cylinder_info(t_cylinder *cy);
void			move_cylinder(t_cylinder *cy, t_vec mv);
void			resize_cylinder(t_cylinder *cy, double amount, int flag);
void			rotate_cylinder(t_cylinder *cy, t_vec axis, double angle);
#endif
