/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 13:03:25 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/09 17:33:06 by kanlee           ###   ########.fr       */
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

t_sphere		*new_sphere(t_vec center, double radius, t_color color);
void			free_sphere(t_sphere *sp);

void move_sphere(t_sphere *sp, double dx, double dy);
void get_sphere_info(char **msg, t_sphere *sp);
#endif
