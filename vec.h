/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 13:04:28 by kanlee            #+#    #+#             */
/*   Updated: 2020/12/07 14:23:17 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC_H
# define VEC_H

typedef struct	s_vec
{
	double		x;
	double		y;
	double		z;
}				t_vec;

t_vec v_new(double x, double y, double z);
t_vec v_add(t_vec a, t_vec b);
t_vec v_sub(t_vec a, t_vec b);
t_vec v_mul(t_vec a, double b);
t_vec v_div(t_vec a, double b);
double v_len_squared(t_vec a);
double v_len(t_vec a);
t_vec v_unit(t_vec a);
double v_dot(t_vec a, t_vec b);
t_vec v_cross(t_vec a, t_vec b);

t_vec rotateX(t_vec a, double rad);
t_vec rotateY(t_vec a, double rad);

#endif
