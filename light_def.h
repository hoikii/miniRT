
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_def.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 14:48:37 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/15 17:54:53 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_DEF_H
# define LIGHT_DEF_H

typedef struct	s_light {
	t_vec		position;
	double		brightness;
	t_color		color;
}				t_light;

#endif
