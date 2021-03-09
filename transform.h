/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 03:57:25 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/08 04:29:35 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRANSFORM_H
# define TRANSFORM_H

# include "minirt.h"

void move_x(t_mlx *rt, double amount);
void move_z(t_mlx *rt, double amount);
void rotate_pitch(t_mlx *rt, int amount);
void rotate_yaw(t_mlx *rt, int amount);

#endif
