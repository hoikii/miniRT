/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_value.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 16:21:14 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/02 17:29:38 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_VALUE_H
# define PARSE_VALUE_H

int		get_integer(char *str, int *ret);
int		get_double(char *str, double *ret);
int		get_color(char *str, t_color *ret);
int		get_vector(char *str, t_vec *ret);
int		get_vector_norm(char *str, t_vec *ret);

#endif
