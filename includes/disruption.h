/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disruption.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 14:44:24 by kanlee            #+#    #+#             */
/*   Updated: 2021/04/04 01:29:17 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISRUPTION_H
# define DISRUPTION_H

# include "minirt.h"
# include "ray.h"

t_color	rainbow(t_rec rec);
t_color	checkerboard(t_rec rec, t_mlx *rt);
t_vec	wave(t_rec rec, t_ray ray);

#endif
