/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 22:39:51 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/30 18:51:43 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SQUARE_H
# define SQUARE_H

# include "vec.h"
# include "color.h"
# include "minirt.h"

typedef struct		s_square {
	t_vec			center;
	t_vec			normal;
	double			size;
	t_color			color;
	t_vec			up;
	t_vec			p1;
	t_vec			p2;
	t_vec			p3;
	t_vec			p4;
	t_bonus_attr	bonus;
}					t_square;

void			fill_square_info(t_square *sq, int is_init);
void			move_square(t_square *sq, t_vec mv);
void			resize_square(t_square *sq, double amount);
void			rotate_square(t_square *sq, t_vec axis, double angle);

#endif
