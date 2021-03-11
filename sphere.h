/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 13:03:25 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/11 02:04:35 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERE_H
# define SPHERE_H

# include "color.h"
# include "vec.h"

typedef struct	s_sphere {
	t_vec		center;
	double		radius;
	t_color		color;
}				t_sphere;

void			move_sphere(t_sphere *sp, double dx, double dy, double dz);
void			resize_sphere(t_sphere *sp, double amount);
#endif
