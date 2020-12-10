/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 11:18:47 by kanlee            #+#    #+#             */
/*   Updated: 2020/12/09 18:11:10 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_UTILS_H
# define MATH_UTILS_H

double	degree_to_radian(double degree);
double	rtod(double rad);
double	clamp(double x, double min, double max);
double	quadratic_solve(double a, double b, double c);

#endif
