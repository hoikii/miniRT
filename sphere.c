/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 16:35:03 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/11 02:16:28 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sphere.h"

void	move_sphere(t_sphere *sp, double dx, double dy, double dz)
{
	if (dx != 0)
		sp->center = v_add(sp->center, v_new(dx, 0, 0));
	if (dy != 0)
		sp->center = v_add(sp->center, v_new(0, dy, 0));
	if (dz != 0)
		sp->center = v_add(sp->center, v_new(0, 0, dz));
}

void	resize_sphere(t_sphere *sp, double amount)
{
	sp->radius += amount;
}
