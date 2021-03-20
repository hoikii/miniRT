/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 15:16:17 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/20 16:43:31 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLANE_H
# define PLANE_H

# include "color.h"
# include "vec.h"

typedef struct	s_plane {
	t_vec		point;
	t_vec		normal;
	t_color		color;
	double		anglex;
	double		angley;
}				t_plane;

void			move_plane(t_plane *pl, t_vec mv);
void			rotate_plane(t_plane *pl, double dx, double dy);

#endif
