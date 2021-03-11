/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 14:09:53 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/11 02:43:07 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "vec.h"

double	v_len_squared(t_vec a)
{
	return (a.x * a.x + a.y * a.y + a.z * a.z);
}

double	v_len(t_vec a)
{
	return (sqrt(v_len_squared(a)));
}

t_vec	v_unit(t_vec a)
{
	return (v_div(a, v_len(a)));
}

double	v_dot(t_vec a, t_vec b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec	v_cross(t_vec a, t_vec b)
{
	t_vec	ret;

	ret.x = a.y * b.z - a.z * b.y;
	ret.y = a.z * b.x - a.x * b.z;
	ret.z = a.x * b.y - a.y * b.x;
	return (ret);
}
