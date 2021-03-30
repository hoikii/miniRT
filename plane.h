/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 15:16:17 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/30 18:51:02 by kanlee           ###   ########.fr       */
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
	t_bonus_attr	bonus;
}					t_plane;

void			move_plane(t_plane *pl, t_vec mv);
void			rotate_plane(t_plane *pl, t_vec axis, double angle);

#endif
