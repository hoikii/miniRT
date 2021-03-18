/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 21:29:59 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/18 09:36:17 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HIT_H
# define HIT_H

# include <math.h>
# include "objects.h"
# include "math_utils.h"

int	hit_sphere(t_sphere *sp, t_ray ray, double tmax, t_rec *rec);
int	hit_plane(t_plane *pl, t_ray ray, double tmax, t_rec *rec);
int	hit_triangle(t_triangle *tri, t_ray ray, double tmax, t_rec *rec);
int	hit_square(t_square *sq, t_ray ray, double tmax, t_rec *rec);
int	hit_cylinder(t_cylinder *cy, t_ray ray, double tmax, t_rec *rec);
int	hit_cylinder_caps(t_cylinder *cy, t_ray ray, double tmax, t_rec *rec);

#endif
