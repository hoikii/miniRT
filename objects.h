/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 21:29:05 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/15 14:36:24 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include "minirt.h"
# include "ray.h"
# include "sphere.h"
# include "plane.h"
# include "triangle.h"
# include "square.h"
# include "cylinder.h"

int		hit(t_objects obj, t_ray ray, double tmax, t_rec *rec);

void	show_object_info(int idx, t_mlx *rt);
void	move_object(t_mlx *rt, double dx, double dy, double dz);
void	resize_object(t_mlx *rt, double amount);
void	rotate_object(t_mlx *rt, double dx, double dy);
#endif
