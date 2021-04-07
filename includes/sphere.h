/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 13:03:25 by kanlee            #+#    #+#             */
/*   Updated: 2021/04/07 20:41:49 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERE_H
# define SPHERE_H

# include "color.h"
# include "vec.h"
# include "minirt.h"

typedef struct		s_sphere {
	t_vec			center;
	double			radius;
	t_color			color;
	t_bonus_attr	bonus;
}					t_sphere;

void			move_sphere(t_sphere *sp, t_vec mv);
void			resize_sphere(t_sphere *sp, double amount);
void			free_texture(t_sphere *sp, t_mlx *rt);
#endif
