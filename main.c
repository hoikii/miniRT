/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 10:03:16 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/03 22:01:56 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <float.h>
#include <math.h>
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
	return ;
}

int			main(int ac, char **av)
{
	t_mlx	rt;
	char	*filepath;
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
		rt.win = mlx_new_window(rt.mlx, rt.screen_width, rt.screen_height, "raytracer");
	render_scene(&rt, save_bmp);
#ifdef LINUX
	mlx_hook(rt.win, CLIENTMESSAGE, WM_DELETE_WINDOW, close_window, &rt);
#else
	mlx_hook(rt.win, DESTROYNOTIFY, STRUCTURENOTIFYMASK, close_window, &rt);
#endif
	mlx_hook(rt.win, KEYPRESS, KEYPRESSMASK, key_pressed, &rt);
	mlx_loop(rt.mlx);
	return (0);
}
