/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 21:29:05 by kanlee            #+#    #+#             */
/*   Updated: 2020/12/09 18:22:53 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include "minirt.h"
# include "ray.h"
# include "sphere.h"
# include "plane.h"
# include "triangle.h"

int hit_sphere(t_sphere *sp, t_ray ray, double tmax, t_rec *rec);
int hit_plane(t_plane *pl, t_ray ray, double tmax, t_rec *rec);
int hit_triangle(t_triangle *tri, t_ray ray, double tmax, t_rec *rec);
int hit(t_objects obj, t_ray ray, double tmax, t_rec *rec);

#endif
