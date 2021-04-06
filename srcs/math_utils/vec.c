/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 14:09:53 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/11 02:42:49 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

t_vec	v_new(double x, double y, double z)
{
	t_vec	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

t_vec	v_add(t_vec a, t_vec b)
{
	t_vec	ret;

	ret.x = a.x + b.x;
	ret.y = a.y + b.y;
	ret.z = a.z + b.z;
	return (ret);
}

t_vec	v_sub(t_vec a, t_vec b)
{
	t_vec	ret;

	ret.x = a.x - b.x;
	ret.y = a.y - b.y;
	ret.z = a.z - b.z;
	return (ret);
}

t_vec	v_mul(t_vec a, double b)
{
	t_vec	ret;

	ret.x = a.x * b;
	ret.y = a.y * b;
	ret.z = a.z * b;
	return (ret);
}

t_vec	v_div(t_vec a, double b)
{
	t_vec	ret;

	ret.x = a.x / b;
	ret.y = a.y / b;
	ret.z = a.z / b;
	return (ret);
}
