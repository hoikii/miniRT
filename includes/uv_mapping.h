/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_mapping.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 14:44:24 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/28 05:11:20 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UV_MAPPING_H
# define UV_MAPPING_H

# include "minirt.h"

t_color	uvmap(t_rec rec, t_mlx *rt);
t_color	skymap(t_vec raydir, t_mlx *rt);

#endif
