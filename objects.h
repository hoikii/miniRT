/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 21:29:05 by kanlee            #+#    #+#             */
/*   Updated: 2020/11/29 23:26:36 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include "minirt.h"
# include "ray.h"
# include "sphere.h"
# include "plane.h"
# include "triangle.h"


double hit_sphere(t_sphere *sp, t_ray ray, double tmax, t_rec *rec);
double hit_plane(t_plane *pl, t_ray ray, double tmax, t_rec *rec);
double hit_triangle(t_triangle *tri, t_ray ray, double tmax, t_rec *rec);

#endif
