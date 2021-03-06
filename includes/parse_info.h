/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_info.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 11:18:13 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/28 05:00:56 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_INFO_H
# define PARSE_INFO_H

void	parse_resolution(char *line, t_mlx *rt, int linenum);
void	parse_ambient(char *line, t_mlx *rt, int linenum);
void	parse_camera(char *line, t_mlx *rt, int linenum);
void	parse_light(char *line, t_mlx *rt, int linenum);
void	parse_skybox(char *line, t_mlx *rt, int linenum);

#endif
