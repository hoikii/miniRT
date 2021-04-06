/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 16:35:03 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/31 00:01:31 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sphere.h"
#include "minirt.h"

void	move_sphere(t_sphere *sp, t_vec mv)
{
	sp->center = v_add(sp->center, mv);
}

void	resize_sphere(t_sphere *sp, double amount)
{
	if (sp->radius + amount > 0 + EPSILON)
		sp->radius += amount;
}
