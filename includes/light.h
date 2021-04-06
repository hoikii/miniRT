/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 14:48:37 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/20 17:27:02 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H

# include "minirt.h"
# include "color.h"
# include "ray.h"

t_light			*new_light(t_vec position, double brightness, t_color color);
void			free_light(t_light *l);
t_color			apply_light(t_rec rec, int idx, t_mlx *rt);
void			move_light(t_mlx *rt, t_vec mv);

#endif
