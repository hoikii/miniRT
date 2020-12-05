/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 16:35:03 by kanlee            #+#    #+#             */
/*   Updated: 2020/11/29 22:52:51 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sphere.h"

t_sphere *new_sphere(t_vec center, double radius, t_color color)
{
	t_sphere *sp = malloc(sizeof(t_sphere));
	sp->center = center;
	sp->radius = radius;
	sp->color = color;
	return sp;
}

void free_sphere(t_sphere *sp)
{
	free(sp);
	return ;
}
