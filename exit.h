/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 15:30:51 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/02 14:14:58 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXIT_H
# define EXIT_H

# include "minirt.h"

int		close_window(t_mlx *param);
void	exit_error(char *str, t_mlx *rt);
void	exit_error_ln(char *str, t_mlx *rt, int linenumber);
void	exit_errorr(char *str, t_mlx *rt, int linenumber);

#endif
