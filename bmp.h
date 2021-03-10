/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 00:39:48 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/10 18:07:45 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BMP_H
# define BMP_H
# include "minirt.h"

# define BMP_FILE_HEADER_SIZE 14
# define BMP_INFO_HEADER_SIZE 40

void	create_bmp_image(t_img image, t_mlx *rt);

#endif
