/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 13:06:30 by kanlee            #+#    #+#             */
/*   Updated: 2020/12/09 11:11:08 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

typedef struct	s_color {
	double		r;
	double		g;
	double		b;
}				t_color;

t_color			color(double r, double g, double b);
t_color			c_mix(t_color a, t_color b);
t_color			c_add(t_color a, t_color b);
t_color			c_mul(t_color a, double b);
int				color_to_int(t_color c);

#endif
