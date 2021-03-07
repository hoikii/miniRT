/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 08:48:30 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/07 09:22:30 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>
#include "minirt.h"
#include "ray.h"
#include "camera.h"
#include "sphere.h"
#include "plane.h"
#include "light.h"
#include "key.h"
#include "math_utils.h"
#include "objects.h"
#include "vec.h"
#include "bmp.h"
#include "trace_ray.h"
#include "libft/libft.h"

/*
** Use write() instead of printf() because flusing buffer is needed but
** fflush() or setbuf() isn't allowed.
*/

static void	print_progress(int tid, int current)
{
	int i;

	if (tid == -1)
	{
		ft_putstr_fd("\rrenndering ", STDOUT);
		ft_putnbr_fd(current, STDOUT);
		ft_putchar_fd('%', STDOUT);
		return ;
	}
	if (g_threads_progress[THREADS_CNT] == 1)
		return ;
	g_threads_progress[THREADS_CNT] = 1;
	ft_putchar_fd('\r', STDOUT);
	g_threads_progress[tid] = current;
	i = -1;
	while (++i < THREADS_CNT)
	{
		ft_putchar_fd('t', STDOUT);
		ft_putnbr_fd(i, STDOUT);
		ft_putstr_fd(": ", STDOUT);
		ft_putnbr_fd(g_threads_progress[i], STDOUT);
		ft_putstr_fd("%   ", STDOUT);
	}
	g_threads_progress[THREADS_CNT] = 0;
}

static void	draw_thread(t_mlx *rt, int tid)
{
	int			i;
	int			j;
	t_ray		ray;
	t_viewport	vp;

	set_viewport(rt, &vp);
	ray.origin = ((t_cam *)(rt->cam_list->content))->origin;
	i = -1;
	while (++i < rt->screen_height)
	{
		if (i % THREADS_CNT != tid)
			continue;
		j = -1;
		while (++j < rt->screen_width)
		{
			ray.direction = set_ray_direction(ray, vp,
					(double)i / (rt->screen_height - 1),
					(double)j / (rt->screen_width - 1));
			set_pixel_color(rt, i, j,
					trace_ray(ray, REFLECTION_DEPTH, rt));
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
	pthread_exit((void *)0);
}

static void	draw(t_mlx *rt)
{
	int			i;
	int			j;
	t_ray		ray;
	t_viewport	vp;

	set_viewport(rt, &vp);
	ray.origin = ((t_cam *)(rt->cam_list->content))->origin;
	i = -1;
	while (++i < rt->screen_height)
	{
		j = -1;
		while (++j < rt->screen_width)
		{
			ray.direction = set_ray_direction(ray, vp,
					(double)i / (rt->screen_height - 1),
					(double)j / (rt->screen_width - 1));
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
		mlx_put_image_to_window(rt->mlx, rt->win, camera->image.img_ptr, 0, 0);
	return ;
}
