/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 11:15:33 by kanlee            #+#    #+#             */
/*   Updated: 2020/11/29 23:36:28 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "math_utils.h"

double degree_to_radian(double degree)
{
	return (degree * PI / 180.0);
}

double rtod(double rad)
{
	return (rad * 180.0 / PI);
}
