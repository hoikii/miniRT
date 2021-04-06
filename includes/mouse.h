/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 21:15:31 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/27 16:16:12 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOUSE_H
# define MOUSE_H

# include "minirt.h"

# define MOUSE_LCLICK 1

int mouse_clicked(int btn, int click_x, int click_y, t_mlx *rt);

#endif
