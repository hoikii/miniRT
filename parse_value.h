/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_value.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 16:21:14 by kanlee            #+#    #+#             */
/*   Updated: 2020/12/05 18:19:11 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_VALUE_H
# define PARSE_VALUE_H

int		get_integer(char **line);
double	get_double(char **line);
t_color	get_color(char **line);
t_vec	get_vector(char **line);

#endif
