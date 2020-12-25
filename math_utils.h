/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 11:18:47 by kanlee            #+#    #+#             */
/*   Updated: 2020/12/23 14:38:21 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_UTILS_H
# define MATH_UTILS_H

typedef struct	s_coef {
	double		a;
	double		b;
	double		c;
}				t_coef;

double	degree_to_radian(double degree);
double	rtod(double rad);
double	clamp(double x, double min, double max);
double	quadratic_solve(double a, double b, double c);
int		quadratic_solve2(double *root1, double *root2, t_coef coef);

#endif
