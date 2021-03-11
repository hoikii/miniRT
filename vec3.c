/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 14:09:53 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/11 02:43:17 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "vec.h"

t_vec	v_rotate_x(t_vec a, double rad)
{
	t_vec	ret;

	ret.x = a.x;
	ret.z = a.z * cos(rad) - a.y * sin(rad);
	ret.y = a.z * sin(rad) + a.y * cos(rad);
	return (ret);
}

t_vec	v_rotate_y(t_vec a, double rad)
{
	t_vec	ret;

	ret.x = a.x * cos(rad) - a.z * sin(rad);
	ret.y = a.y;
	ret.z = a.x * sin(rad) + a.z * cos(rad);
	return (ret);
}
