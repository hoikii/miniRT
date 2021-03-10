/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 15:16:17 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/10 14:22:20 by kanlee           ###   ########.fr       */
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

t_plane			*new_plane(t_vec point, t_vec normal, t_color color);
void			free_plane(t_plane *pl);
void			move_plane(t_plane *pl, double dx, double dz);
void			rotate_plane(t_plane *pl, double dx, double dy);

#endif
