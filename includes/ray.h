/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 13:12:48 by kanlee            #+#    #+#             */
/*   Updated: 2020/12/12 03:08:01 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "vec.h"

typedef struct	s_ray {
	t_vec		origin;
	t_vec		direction;
}				t_ray;

t_ray			new_ray(t_vec origin, t_vec direction);
t_vec			ray_at(t_ray r, double t);
#endif
