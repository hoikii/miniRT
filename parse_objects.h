/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 16:48:35 by kanlee            #+#    #+#             */
/*   Updated: 2020/12/05 18:17:47 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_OBJECTS_H
# define PARSE_OBJECTS_H

# include "minirt.h"

void parse_sphere(char *line, t_mlx *rt);
void parse_plane(char *line, t_mlx *rt);
void parse_triangle(char *line, t_mlx *rt);

#endif
