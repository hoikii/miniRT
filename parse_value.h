/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_value.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 16:21:14 by kanlee            #+#    #+#             */
/*   Updated: 2021/04/05 21:02:26 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_VALUE_H
# define PARSE_VALUE_H

int		get_integer(char *str, int *ret);
int		get_double(char *str, double *ret);
int		get_color(char *str, t_color *ret);
int		get_vector(char *str, t_vec *ret);
int		get_vector_norm(char *str, t_vec *ret);

int		get_bonus(char **str, t_bonus_attr *bonus, int type, t_mlx *rt);
int		get_texture(char *filepath, t_img *ret, t_mlx *rt);

#endif
