/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 22:47:30 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/30 18:51:29 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRIANGLE_H
# define TRIANGLE_H

# include "color.h"
# include "vec.h"
# include "minirt.h"

typedef struct		s_triangle {
	t_vec			p1;
	t_vec			p2;
	t_vec			p3;
	t_vec			normal;
	t_color			color;
	t_bonus_attr	bonus;
}					t_triangle;

t_triangle		new_triangle(t_vec p1, t_vec p2, t_vec p3, t_color color);
void			move_triangle(t_triangle *tri, t_vec mv);

#endif
