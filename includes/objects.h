/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 21:29:05 by kanlee            #+#    #+#             */
/*   Updated: 2021/04/03 23:42:33 by kanlee           ###   ########.fr       */
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
# include "cube.h"
# include "pyramid.h"

int		hit(t_objects obj, t_ray ray, double tmax, t_rec *rec);

void	move_object(t_mlx *rt, t_vec mv);
void	resize_object(t_mlx *rt, double amount, int flag);
void	rotate_object(t_mlx *rt, t_vec axis, double angle);
int		modify_wave_attr(t_mlx *rt, int is_brace, int incdec);
#endif
