/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 22:47:30 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/09 21:12:22 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRIANGLE_H
# define TRIANGLE_H

# include "color.h"
# include "vec.h"

typedef struct	s_triangle {
	t_vec		p1;
	t_vec		p2;
	t_vec		p3;
	t_vec		normal;
	t_color		color;
}				t_triangle;

t_triangle		*new_triangle(t_vec point1, t_vec point2, t_vec point3,
		t_color color);
void			free_triangle(t_triangle *tri);
void			move_triangle(t_triangle *tri, double dx, double dz);

#endif
