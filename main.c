/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 10:03:16 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/11 16:47:07 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "ray.h"
#include "camera.h"
#include "objects.h"
#include "light.h"
#include "key.h"
#include "math_utils.h"
#include "parser.h"
#include "error.h"
#include "exit.h"

static void	init_struct(t_mlx *rt)
{
	rt->objs_cnt = 0;
	rt->cam_list = NULL;
	rt->lights_list = NULL;
	rt->resolution_declared = 0;
	rt->ambient_declared = 0;
	rt->win = NULL;
	rt->transform_mode = MODE_CAM;
	rt->obj_selected_idx = 0;
	return ;
}

static long	get_kpressmask(void)
{
	if (LINUX_ENV_SWITCH)
		return (1L << 0);
	else
		return (1L);
}

static void	prn_usage(void)
{
	printf("============================================\n");
	printf("wasd: move    arrows: rotate     o:cam<->obj\n");
	printf("+-: fov in cam mode, size in obj mode\n");
	printf("============================================\n");
}

int			main(int ac, char **av)
{
	t_mlx	rt;
	int		save_bmp;

	init_struct(&rt);
	rt.mlx = mlx_init();
	if (ac < 2 || ac > 3 || (ac == 3 && !ft_strequ(av[2], "-save")))
		exit_error("Usage: miniRT scene.rt [-save]", &rt);
	parser(av[1], &rt);
	save_bmp = 0;
	if (ac == 3)
		save_bmp = 1;
	else
	{
		rt.win = mlx_new_window(rt.mlx,
				rt.screen_width, rt.screen_height, "miniRT");
		prn_usage();
	}
	render_scene(&rt, save_bmp);
#if 0
	if (LINUX_ENV_SWITCH)
		mlx_hook(rt.win, CLIENTMESSAGE, WM_DELETE_WINDOW, close_window, &rt);
	else
#endif
		mlx_hook(rt.win, DESTROYNOTIFY, STRUCTURENOTIFYMASK, close_window, &rt);
//	mlx_hook(rt.win, KEYPRESS, get_kpressmask(), key_pressed, &rt);
	mlx_hook(rt.win, KEYPRESS, KEYPRESSMASK, key_pressed, &rt);
	mlx_loop(rt.mlx);
	return (0);
}
