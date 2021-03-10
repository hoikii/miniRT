/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 21:29:59 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/10 18:23:46 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HIT_UTILS_H
# define HIT_UTILS_H

# include <math.h>
# include "objects.h"
# include "math_utils.h"

int	check_edge(t_vec p1, t_vec p2, t_vec hit_point, t_vec normal);
int is_cylinder_range(t_cylinder *cy, t_ray ray, double t);

#endif
