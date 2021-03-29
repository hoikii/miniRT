/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 14:09:53 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/29 03:23:17 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "vec.h"
#include "math_utils.h"

t_vec	v_rotate(t_vec v, t_vec axis, double angle)
{
	t_vec	v_proj;
	t_vec	v_perp;
	t_vec	v_perp_r;
	t_vec	w;

	angle = degree_to_radian(angle);
	w = v_cross(axis, v);
	v_proj = v_mul(axis, v_dot(v, axis));
	v_perp = v_sub(v, v_proj);
	v_perp_r = v_add(v_mul(v_perp, cos(angle)), v_mul(w, sin(angle)));
	v = v_unit(v_add(v_proj, v_perp_r));
	return (v);
}
