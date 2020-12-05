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

int close_window(t_mlx *param) {
	mlx_destroy_window(param->mlx, param->win);
	ft_lstclear(&(param->objects), free);
	ft_lstclear(&(param->lights), free);
	exit(0);
}

int main() {
	t_mlx rt;


	// Camera
	rt.cam.origin = v_new(-2,2,-1);
	rt.cam.direction = v_unit(v_new(2,-2,2));
//	rt.cam.origin = v_new(0,0,-2);
//	rt.cam.direction = v_unit(v_new(0,0,1));
	rt.cam.origin = v_new(0,2,-2);
	rt.cam.direction = v_unit(v_new(0,-1,1));
	rt.cam.fov = 90;
	rt.cam.vup = v_new(0,1,0);
	rt.cam.tanx = rtod(atan(rt.cam.direction.x / rt.cam.direction.z));
	rt.cam.tany = rtod(-1 * asin(rt.cam.direction.y));

	// Lights
	t_ambient ambient;
	ambient.brightness = 0.2;
	ambient.color = color(0.6, 0.6, 0.6);
	rt.ambient = ambient;

	t_list *lights;
	lights =                ft_lstnew(new_light(v_new( -3, 0.7, -0.5), 0.3, color(1,1,1)),0);
	ft_lstadd_back(&lights, ft_lstnew(new_light(v_new(  2, 0.4, -0.5), 0.3, color(1,1,1)),0));
	rt.lights = lights;


	parser(&rt);


	// Render
	rt.mlx = mlx_init();
	rt.win = mlx_new_window(rt.mlx, rt.screen_width, rt.screen_height, "raytracer");
	rt.img = mlx_new_image(rt.mlx, rt.screen_width, rt.screen_height);
	rt.imgdata = mlx_get_data_addr(rt.img, &rt.bpp, &rt.size_line, &rt.endian);

	printf("mlx window running\n");
	setbuf(stdout,NULL);
	draw(&rt);

	//mlx_key_hook(mlx.win, key_hook, &mlx);
	mlx_hook(rt.win, X_EVENT_KEY_EXIT, 0, close_window, &rt);
	mlx_hook(rt.win, X_EVENT_KEY_PRESS, 0, key_pressed, &rt);
	mlx_loop(rt.mlx);
	return 0;
}

