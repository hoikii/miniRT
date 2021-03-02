/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 16:18:34 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/01 21:50:57 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_UTILS_H
# define PARSER_UTILS_H

# include "minirt.h"
# define SUCCESS 0
# define FAIL 1

void skip_blank(char **line);
void skip_sep(char **line);
void append_object(void *obj, int type, t_mlx *rt);
void free_words(char **words);

#endif
