/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerboard.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 14:44:24 by kanlee            #+#    #+#             */
/*   Updated: 2021/04/05 03:00:41 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKERBOARD_H
# define CHECKERBOARD_H

# include "minirt.h"

t_color	checker_sphere(t_rec rec);
t_color	checker_plane(t_rec rec, t_mlx *rt);
t_color	checker_square(t_rec rec, t_mlx *rt);
t_color	checker_cylinder(t_rec rec, t_mlx *rt);

#endif
