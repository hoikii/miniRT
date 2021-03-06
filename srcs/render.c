/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 08:48:30 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/26 19:02:26 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>
#include "minirt.h"
#include "ray.h"
#include "camera.h"
#include "light.h"
#include "key.h"
#include "math_utils.h"
#include "objects.h"
#include "vec.h"
#include "bmp.h"
#include "trace_ray.h"
#include "progress.h"
#include "show_transform_info.h"
#include "color_filter.h"
#include "supersample.h"

int			put_img_to_window(t_mlx *rt)
{
	t_img	image;

	image = ((t_cam *)(rt->cam_list->content))->image;
	if (rt->color_filter == FILTER_NONE)
		mlx_put_image_to_window(rt->mlx, rt->win, image.img_ptr, 0, 0);
	else
		apply_color_filter(rt);
	if (rt->transform_mode == MODE_OBJ)
		show_transform_info(rt->obj_selected_idx, rt);
	else if (rt->transform_mode == MODE_LIGHT)
		show_transform_info(rt->light_sel_idx, rt);
	return (0);
}

static void	draw_thread(t_mlx *rt, int tid)
{
	int			i;
	int			j;
	t_ray		ray;

	set_viewport(rt);
	ray.origin = ((t_cam *)(rt->cam_list->content))->origin;
	i = -1;
	while (++i < rt->screen_height)
	{
		if (i % THREADS_CNT != tid)
			continue ;
		j = -1;
		while (++j < rt->screen_width)
		{
			if (rt->anti_aliasing == 1)
				supersample(ray, i, j, rt);
			else
			{
				ray.direction = set_ray_direction(ray, i, j, rt);
				set_pixel_color(rt, i, j, trace_ray(ray, REFLECTION_DEPTH, rt));
			}
		}
		print_progress(tid, (i + 1) * 100 / rt->screen_height);
	}
	return ;
}

static void	*thread_entry(void *arg)
{
	t_mlx		*rt;
	int			tid;

	rt = ((t_thread *)arg)->mlx;
	tid = ((t_thread *)arg)->tid;
	draw_thread(rt, tid);
	pthread_exit((void *)(0));
}

static void	draw(t_mlx *rt)
{
	int			i;
	int			j;
	t_ray		ray;

	set_viewport(rt);
	ray.origin = ((t_cam *)(rt->cam_list->content))->origin;
	i = -1;
	while (++i < rt->screen_height)
	{
		j = -1;
		while (++j < rt->screen_width)
		{
			ray.direction = set_ray_direction(ray, i, j, rt);
			set_pixel_color(rt, i, j,
				trace_ray(ray, REFLECTION_DEPTH, rt));
		}
		print_progress(-1, (i + 1) * 100 / rt->screen_height);
	}
	return ;
}

void		render_scene(t_mlx *rt, int save_bmp)
{
	pthread_t	threads[THREADS_CNT];
	t_thread	arg[THREADS_CNT];
	int			i;
	t_cam		*camera;

	if (BONUS != 1 || THREADS_CNT <= 1)
		draw(rt);
	else
	{
		i = -1;
		while (++i < THREADS_CNT)
		{
			arg[i].mlx = rt;
			arg[i].tid = i;
			pthread_create(&threads[i], NULL, &thread_entry, (void *)(&arg[i]));
		}
		while (--i >= 0)
			pthread_join(threads[i], NULL);
	}
	camera = rt->cam_list->content;
	if (save_bmp)
		create_bmp_image(camera->image, rt);
	else
		put_img_to_window(rt);
	return ;
}
