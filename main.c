/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 10:03:16 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/27 16:33:31 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "key.h"
#include "mouse.h"
#include "parser.h"
#include "objects.h"
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
	rt->light_sel_idx = 0;
	rt->color_filter = 0;
#if 0
	rt->frequency = 50;
	rt->amplitude = 0.00;
#endif
	rt->anti_aliasing = 0;
	return ;
}

/*
** watch WM_DELETE_WINDOW event on Linux and DestroyNotify on MacOS
** to detect closing a window.
**
** On Linux, window goes blank when minimized and then restored.
** Redraw an image again when detects VisibilityNotify (15) and
** VisibilityChangeMask (1L<<16)
*/

#ifdef LINUX

static void	init_mlx_hook(t_mlx *rt)
{
	mlx_hook(rt->win, CLIENTMESSAGE, WM_DELETE_WINDOW, close_window, rt);
	mlx_hook(rt->win, KEYPRESS, 1L, key_pressed, rt);
	mlx_hook(rt->win, VISIBILITYNOTIFY, (1L << 16), put_img_to_window, rt);
	mlx_mouse_hook(rt->win, mouse_clicked, rt);
}

#else

static void	init_mlx_hook(t_mlx *rt)
{
	mlx_hook(rt->win, DESTROYNOTIFY, STRUCTURENOTIFYMASK, close_window, rt);
	mlx_hook(rt->win, KEYPRESS, 1L, key_pressed, rt);
	mlx_mouse_hook(rt->win, mouse_clicked, rt);
}

#endif

static void	prn_usage(void)
{
	printf("*=============================================================*\n");
	printf("|  wasdqz: move       arrows: rotate    space: change camera  |\n");
	printf("|  c,o,l: cam<->obj<->light                                   |\n");
	printf("|  +-: fov in cam mode, resize in obj mode                    |\n");
	printf("|  */: resize height of cylinder or pyramid                   |\n");
	printf("|  1, 2: change color filter          T: apply Anti-Aliasing  |\n");
	printf("|  Click: change camera direction                             |\n");
	printf("*=============================================================*\n");
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
	init_mlx_hook(&rt);
	mlx_loop(rt.mlx);
	return (0);
}
