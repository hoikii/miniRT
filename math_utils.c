/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 11:15:33 by kanlee            #+#    #+#             */
/*   Updated: 2020/12/09 18:11:22 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "math_utils.h"

double	degree_to_radian(double degree)
{
	return (degree * PI / 180.0);
}

double	rtod(double rad)
{
	return (rad * 180.0 / PI);
}

double	clamp(double x, double min, double max)
{
	if (x < min)
		return (min);
	if (x > max)
		return (max);
	return (x);
}

/*
** Takes three coefficients of quadratic equation and
** returns minimum positive root.
** Returns negative if min root is negative or root doesn't exist.
*/

double	quadratic_solve(double a, double b, double c)
{
	double discriminant;
	double ans;

	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (-1);
	ans = (-b - sqrt(discriminant)) / (2.0 * a);
	if (ans < 0)
		ans = (-b + sqrt(discriminant)) / (2.0 * a);
	return (ans);
}
