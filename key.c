/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 13:02:14 by kanlee            #+#    #+#             */
/*   Updated: 2021/04/05 19:51:41 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key.h"
#include "objects.h"
#include "transform.h"
#include "camera.h"
#include "exit.h"
#include "show_transform_info.h"

static void	key_pressed3(int keycode, t_mlx *rt)
{
	if (keycode == KEY_SPACE)
	{
		rt->cam_list = rt->cam_list->next;
		render_scene(rt, 0);
	}
	else if (BONUS && keycode == KEY_T)
	{
		rt->anti_aliasing ^= 1;
		render_scene(rt, 0);
	}
	else if (BONUS && rt->transform_mode == MODE_OBJ
		&& (keycode == KEY_COMMA || keycode == KEY_LB))
	{
		if (modify_wave_attr(rt, keycode == KEY_LB, -1))
			render_scene(rt, 0);
	}
	else if (BONUS && rt->transform_mode == MODE_OBJ
		&& (keycode == KEY_PERIOD || keycode == KEY_RB))
	{
		if (modify_wave_attr(rt, keycode == KEY_RB, 1))
			render_scene(rt, 0);
	}
	else
		show_keycode(keycode, rt);
}

static void	key_pressed2(int keycode, t_mlx *rt)
{
	if (keycode == KEY_O && rt->objs_cnt > 0)
	{
		if (rt->transform_mode == MODE_OBJ)
			rt->obj_selected_idx = (rt->obj_selected_idx + 1) % rt->objs_cnt;
		else
			rt->transform_mode = MODE_OBJ;
		put_img_to_window(rt);
	}
	else if (keycode == KEY_L && rt->lights_cnt > 0)
	{
		if (rt->transform_mode == MODE_LIGHT)
			rt->light_sel_idx = (rt->light_sel_idx + 1) % rt->lights_cnt;
		else
			rt->transform_mode = MODE_LIGHT;
		put_img_to_window(rt);
	}
	else if (keycode == KEY_C)
	{
		rt->transform_mode = MODE_CAM;
		put_img_to_window(rt);
	}
	else
		key_pressed3(keycode, rt);
}

int			key_pressed(int keycode, t_mlx *rt)
{
	if (keycode == KEY_ESC)
		close_window(rt);
	else if (keycode == KEY_W || keycode == KEY_A || keycode == KEY_S
		|| keycode == KEY_D || keycode == KEY_Q || keycode == KEY_Z)
		key_wasd(keycode, rt);
	else if (keycode == KEY_LEFT || keycode == KEY_RIGHT
		|| keycode == KEY_UP || keycode == KEY_DOWN)
		key_arrow(keycode, rt);
	else if (keycode == KEY_PLUS || keycode == KEY_MINUS || keycode == KEY_MUL
		|| keycode == KEY_NP_PLUS || keycode == KEY_NP_MINUS
		|| keycode == KEY_NP_MUL || keycode == KEY_DIV || keycode == KEY_NP_DIV)
		key_sign(keycode, rt);
	else if (BONUS && (keycode == KEY_1 || keycode == KEY_2))
	{
		if (keycode == KEY_2)
			rt->color_filter = (rt->color_filter + 1) % FILTER_CNT;
		else
			rt->color_filter = (rt->color_filter + FILTER_CNT - 1) % FILTER_CNT;
		put_img_to_window(rt);
	}
	else
		key_pressed2(keycode, rt);
	return (0);
}
