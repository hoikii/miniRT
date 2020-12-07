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

int close_window(t_mlx *param) {
	int i;

	mlx_destroy_window(param->mlx, param->win);
	i = -1;
	while (++i < param->objs_cnt)
		free(param->objects_array[i].data);
	ft_lstclear(&(param->lights), free);
	ft_lstclear(&(param->cam_list_head), free);
	exit(0);
}

int main(int ac, char **av) {
	t_mlx rt;

	// Lights
	t_ambient ambient;
	ambient.brightness = 0.2;
	ambient.color = color(0.6, 0.6, 0.6);
	rt.ambient = ambient;

	t_list *lights;
	lights =                ft_lstnew(new_light(v_new( -3, 0.7, -0.5), 0.3, color(1,1,1)),0);
	ft_lstadd_back(&lights, ft_lstnew(new_light(v_new(  2, 0.4, -0.5), 0.3, color(1,1,1)),0));
	rt.lights = lights;

	

	rt.objs_cnt = 0;
	rt.cam_list = NULL;
	char *filepath;
	if (ac == 1)
		filepath = "smpl.rt";
	if (parser(filepath, &rt) != SUCCESS)
		printf("parse failed");


	// Render
	rt.mlx = mlx_init();
	rt.win = mlx_new_window(rt.mlx, rt.screen_width, rt.screen_height, "raytracer");
	rt.img = mlx_new_image(rt.mlx, rt.screen_width, rt.screen_height);
	rt.imgdata = mlx_get_data_addr(rt.img, &rt.bpp, &rt.size_line, &rt.endian);

	printf("mlx window running\n");
	setbuf(stdout,NULL);
	draw(&rt);

	//mlx_key_hook(mlx.win, key_hook, &mlx);
#ifdef LINUX
	mlx_hook(rt.win, CLIENTMESSAGE, WM_DELETE_WINDOW, close_window, &rt);
#else
	mlx_hook(rt.win, DESTROYNOTIFY, STRUCTURENOTIFYMASK, close_window, &rt);
#endif
	mlx_hook(rt.win, KEYPRESS, KEYPRESSMASK, key_pressed, &rt);
	mlx_loop(rt.mlx);
	return 0;
}

