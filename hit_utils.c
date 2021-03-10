/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 21:29:59 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/10 18:28:30 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "objects.h"
#include "hit.h"
#include "math_utils.h"

int	check_edge(t_vec p1, t_vec p2, t_vec hit_point, t_vec normal)
{
	t_vec edge;
	t_vec v_p;

	edge = v_sub(p2, p1);
	v_p = v_sub(hit_point, p1);
	return (v_dot(normal, v_cross(edge, v_p)) >= 0.0);
}

int	is_cylinder_range(t_cylinder *cy, t_ray ray, double t)
{
	t_vec	bottom_center_to_intersection;
	double	range;

	bottom_center_to_intersection = v_sub(ray_at(ray, t), cy->bottom);
	range = v_dot(bottom_center_to_intersection, cy->direction);
	return (0 <= range && range <= cy->height);
}
