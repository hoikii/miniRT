/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 15:16:17 by kanlee            #+#    #+#             */
/*   Updated: 2021/04/04 16:59:43 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLANE_H
# define PLANE_H

# include "color.h"
# include "vec.h"
# include "minirt.h"

typedef struct		s_plane {
	t_vec			point;
	t_vec			normal;
	t_color			color;
	t_vec			u;
	t_vec			v;
	t_bonus_attr	bonus;
}					t_plane;

void				fill_plane_info(t_plane *pl);
void				move_plane(t_plane *pl, t_vec mv);
void				rotate_plane(t_plane *pl, t_vec axis, double angle);

#endif
