/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 21:29:59 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/15 13:43:17 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "objects.h"
#include "hit.h"
#include "math_utils.h"

int		check_edge(t_vec p1, t_vec p2, t_vec hit_point, t_vec normal)
{
	t_vec	edge;
	t_vec	v_p;

	edge = v_sub(p2, p1);
	v_p = v_sub(hit_point, p1);
	return (v_dot(normal, v_cross(edge, v_p)) >= 0.0);
}

void	prepare_cylinder_coef(t_cylinder *cy, t_ray ray, t_coef *coef)
{
	t_vec	vh;
	t_vec	v_a;
	t_vec	v_b;

	vh = v_sub(cy->top, cy->bottom);
	v_a = v_cross(ray.direction, vh);
	v_b = v_cross(v_sub(ray.origin, cy->bottom), vh);
	coef->a = v_len_squared(v_a);
	coef->b = 2 * v_dot(v_a, v_b);
	coef->c = v_len_squared(v_b) - pow(cy->radius * cy->height, 2);
	return ;
}

int		is_cylinder_range(t_cylinder *cy, t_ray ray, double t)
{
	t_vec	bottom_center_to_intersection;
	double	range;

	bottom_center_to_intersection = v_sub(ray_at(ray, t), cy->bottom);
	range = v_dot(bottom_center_to_intersection, cy->direction);
	return (0 <= range && range <= cy->height);
}

t_vec	cylinder_normal(t_cylinder *cy, t_ray ray, double t)
{
	t_vec	btm_to_hp;
	t_vec	res;

	btm_to_hp = v_sub(ray_at(ray, t), cy->bottom);
	res = v_sub(btm_to_hp,
			v_mul(cy->direction, v_dot(btm_to_hp, cy->direction)));
	res = v_unit(res);
	return (res);
}
