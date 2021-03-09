/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 14:09:53 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/09 16:03:53 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "vec.h"

t_vec	v_new(double x, double y, double z)
{
	t_vec v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

t_vec	v_add(t_vec a, t_vec b)
{
	t_vec ret;

	ret.x = a.x + b.x;
	ret.y = a.y + b.y;
	ret.z = a.z + b.z;
	return (ret);
}

t_vec	v_sub(t_vec a, t_vec b)
{
	t_vec ret;

	ret.x = a.x - b.x;
	ret.y = a.y - b.y;
	ret.z = a.z - b.z;
	return (ret);
}

t_vec	v_mul(t_vec a, double b)
{
	t_vec ret;

	ret.x = a.x * b;
	ret.y = a.y * b;
	ret.z = a.z * b;
	return (ret);
}

t_vec	v_div(t_vec a, double b)
{
	t_vec ret;

	ret.x = a.x / b;
	ret.y = a.y / b;
	ret.z = a.z / b;
	return (ret);
}

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
	t_vec ret;

	ret.x = a.y * b.z - a.z * b.y;
	ret.y = a.z * b.x - a.x * b.z;
	ret.z = a.x * b.y - a.y * b.x;
	return (ret);
}

t_vec	v_rotate_x(t_vec a, double rad)
{
	t_vec ret;

	ret.x = a.x;
	ret.z = a.z * cos(rad) - a.y * sin(rad);
	ret.y = a.z * sin(rad) + a.y * cos(rad);
	return (ret);
}

t_vec	v_rotate_y(t_vec a, double rad)
{
	t_vec ret;

	ret.x = a.x * cos(rad) - a.z * sin(rad);
	ret.y = a.y;
	ret.z = a.x * sin(rad) + a.z * cos(rad);
	return (ret);
}
