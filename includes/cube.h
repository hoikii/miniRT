/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 22:39:51 by kanlee            #+#    #+#             */
/*   Updated: 2021/04/08 17:58:28 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include "vec.h"
# include "color.h"
# include "square.h"

typedef struct		s_cube {
	t_vec			center;
	t_vec			normal;
	t_vec			up;
	double			size;
	t_color			color;
	t_square		face[6];
	t_bonus_attr	bonus;
}					t_cube;

void				fill_cube_info(t_cube *cu, int is_init);
void				move_cube(t_cube *cu, t_vec mv);
void				resize_cube(t_cube *cu, double amount);
void				rotate_cube(t_cube *cu, t_vec axis, double angle);

#endif
