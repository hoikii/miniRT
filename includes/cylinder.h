/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 22:49:36 by kanlee            #+#    #+#             */
/*   Updated: 2021/04/08 17:58:17 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CYLINDER_H
# define CYLINDER_H

# include "vec.h"
# include "color.h"
# include "minirt.h"

typedef struct		s_cylinder {
	t_vec			center;
	t_vec			direction;
	double			diameter;
	double			radius;
	double			height;
	t_color			color;
	t_vec			bottom;
	t_vec			top;
	t_vec			meridian;
	t_bonus_attr	bonus;
}					t_cylinder;

void				fill_cylinder_info(t_cylinder *cy);
void				move_cylinder(t_cylinder *cy, t_vec mv);
void				resize_cylinder(t_cylinder *cy, double amount, int flag);
void				rotate_cylinder(t_cylinder *cy, t_vec axis, double angle);
#endif
