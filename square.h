/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 22:39:51 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/02 19:13:34 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SQUARE_H
# define SQUARE_H

# include "vec.h"
# include "color.h"

typedef struct	s_square {
	t_vec		center;
	t_vec		normal;
	double		size;
	t_color		color;
	t_vec		p1;
	t_vec		p2;
	t_vec		p3;
	t_vec		p4;
}				t_square;


t_square	*new_square(t_vec center, t_vec normal, double size, t_color color);
void		free_square(t_square *sq);
void		fill_square_info(t_square *sq);

#endif
