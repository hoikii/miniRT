/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 10:03:16 by kanlee            #+#    #+#             */
/*   Updated: 2021/02/18 20:20:51 by kanlee           ###   ########.fr       */
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

	init_struct(&rt);
	rt.mlx = mlx_init();
	if (ac == 1)
		filepath = "smpl.rt";
	if (parser(filepath, &rt) != SUCCESS)
		printf("parse failed");
	rt.win = mlx_new_window(rt.mlx, rt.screen_width, rt.screen_height, "raytracer");
	printf("mlx window running\n");
	setbuf(stdout, NULL);
	render_scene(&rt);
	//mlx_put_image_to_window(rt.mlx, rt.win, ((t_cam *)(rt.cam_list->content))->image.img, 0, 0);
#ifdef LINUX
	mlx_hook(rt.win, CLIENTMESSAGE, WM_DELETE_WINDOW, close_window, &rt);
#else
	mlx_hook(rt.win, DESTROYNOTIFY, STRUCTURENOTIFYMASK, close_window, &rt);
#endif
	mlx_hook(rt.win, KEYPRESS, KEYPRESSMASK, key_pressed, &rt);
	mlx_loop(rt.mlx);
	return (0);
}
