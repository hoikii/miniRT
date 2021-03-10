/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 16:35:03 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/10 19:17:00 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "sphere.h"

void	move_sphere(t_sphere *sp, double dx, double dz)
{
	if (dx != 0)
		sp->center = v_add(sp->center, v_mul(v_new(1, 0, 0), dx));
	if (dz != 0)
		sp->center = v_add(sp->center, v_mul(v_new(0, 0, 1), dz));
}

void	resize_sphere(t_sphere *sp, double amount)
{
	sp->radius += amount;
}
