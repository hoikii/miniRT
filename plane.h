/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 15:16:17 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/09 21:22:05 by kanlee           ###   ########.fr       */
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
}				t_plane;

t_plane			*new_plane(t_vec point, t_vec normal, t_color color);
void			free_plane(t_plane *pl);
void			move_plane(t_plane *pl, double dx, double dz);

#endif
