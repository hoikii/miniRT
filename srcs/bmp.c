/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 00:39:27 by kanlee            #+#    #+#             */
/*   Updated: 2021/04/08 02:25:12 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "bmp.h"
#include "exit.h"

static void	write_file_header(t_mlx *rt, t_img image, int fd)
{
	unsigned char	file_header[BMP_FILE_HEADER_SIZE];
	int				fsize;
	int				pad_size;

	pad_size = (4 - rt->screen_width % 4) % 4;
	fsize = BMP_FILE_HEADER_SIZE + BMP_INFO_HEADER_SIZE
		+ (rt->screen_width + pad_size) * rt->screen_height * image.bpp / 8;
	ft_memset(file_header, 0, BMP_FILE_HEADER_SIZE);
	file_header[0] = 'B';
	file_header[1] = 'M';
	*(t_uint32_t *)(&file_header[2]) = fsize;
	file_header[10] = BMP_FILE_HEADER_SIZE + BMP_INFO_HEADER_SIZE;
	write(fd, file_header, BMP_FILE_HEADER_SIZE);
	return ;
}

static void	write_info_header(t_mlx *rt, t_img image, int fd)
{
	unsigned char	info_header[BMP_INFO_HEADER_SIZE];
	int				size;
	int				pad_size;

	pad_size = (4 - rt->screen_width % 4) % 4;
	size = (rt->screen_width + pad_size) * rt->screen_height * image.bpp / 8;
	ft_memset(info_header, 0, BMP_INFO_HEADER_SIZE);
	info_header[0] = BMP_INFO_HEADER_SIZE;
	*(t_uint32_t *)(&info_header[4]) = rt->screen_width;
	*(t_uint32_t *)(&info_header[8]) = rt->screen_height;
	*(t_uint16_t *)(&info_header[12]) = 1;
	*(t_uint16_t *)(&info_header[14]) = image.bpp;
	*(t_uint32_t *)(&info_header[20]) = size;
	write(fd, info_header, BMP_INFO_HEADER_SIZE);
	return ;
}

static void	write_data(t_mlx *rt, t_img image, int fd)
{
	int	i;

	i = rt->screen_height;
	while (--i >= 0)
	{
		write(fd, image.imgdata + (i * image.size_line),
			rt->screen_width * (image.bpp / 8));
	}
	return ;
}

void		create_bmp_image(t_img image, t_mlx *rt)
{
	int	fd;

	fd = open("scene.bmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (!fd)
		exit_error("failed to create bmp file", rt);
	write_file_header(rt, image, fd);
	write_info_header(rt, image, fd);
	write_data(rt, image, fd);
	close(fd);
	printf("\nScene is exported as scene.bmp\n");
	close_window(rt);
}
