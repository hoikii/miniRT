/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 21:29:59 by kanlee            #+#    #+#             */
/*   Updated: 2021/04/06 18:37:25 by kanlee           ###   ########.fr       */
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
int	hit_cylinder_cap(t_cylinder *cy, t_ray ray, double tmax, t_rec *rec);
int	hit_cube(t_cube *cu, t_ray ray, double tmax, t_rec *rec);
int	hit_pyramid(t_pyramid *py, t_ray ray, double tmax, t_rec *rec);

#endif
