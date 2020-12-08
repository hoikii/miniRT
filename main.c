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


int main(int ac, char **av) {
	t_mlx rt;

	rt.objs_cnt = 0;
	rt.cam_list = NULL;
	rt.lights = NULL;
	rt.resolution_declared = 0;
	rt.ambient_declared = 0;
	rt.mlx = mlx_init();
	rt.win = NULL;
	char *filepath;
	if (ac == 1)
		filepath = "smpl.rt";
	if (parser(filepath, &rt) != SUCCESS)
		printf("parse failed");


	// Render
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

