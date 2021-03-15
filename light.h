/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 14:48:37 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/15 14:36:52 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H

# include "minirt.h"
# include "color.h"
# include "ray.h"

typedef struct	s_light {
	t_vec		position;
	double		brightness;
	t_color		color;
}				t_light;

t_light			*new_light(t_vec position, double brightness, t_color color);
void			free_light(t_light *l);
t_color			apply_light(t_rec rec, t_list *lights_list, t_mlx *rt);

#endif
