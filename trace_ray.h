/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_ray.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 00:50:40 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/26 18:57:12 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRACE_RAY_H
# define TRACE_RAY_H

# include "minirt.h"
# include "ray.h"
# include "camera.h"

void	set_viewport(t_mlx *rt);
t_vec	set_ray_direction(t_ray ray, double y, double x, t_mlx *rt);
void	set_pixel_color(t_mlx *rt, int y, int x, t_color tcolor);
t_color	trace_ray(t_ray ray, int depth, t_mlx *rt);

#endif
