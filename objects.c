/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 21:29:59 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/15 14:43:11 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "objects.h"
#include "hit.h"
#include "math_utils.h"

char	*g_obj_type_string[5] = {
	"Sphere",
	"Plane",
	"Triangle",
	"Square",
	"Cylinder"};

int		hit(t_objects obj, t_ray ray, double tmax, t_rec *rec)
{
	if (obj.type == TYPE_SPHERE)
		return (hit_sphere(obj.data, ray, tmax, rec));
	if (obj.type == TYPE_PLANE)
		return (hit_plane(obj.data, ray, tmax, rec));
	if (obj.type == TYPE_TRIANGLE)
		return (hit_triangle(obj.data, ray, tmax, rec));
	if (obj.type == TYPE_SQUARE)
		return (hit_square(obj.data, ray, tmax, rec));
	if (obj.type == TYPE_CYLINDER)
		return (hit_cylinder(obj.data, ray, tmax, rec));
	return (0);
}

void	move_object(t_mlx *rt, double dx, double dy, double dz)
{
	t_objects	obj;

	obj = rt->objects_array[rt->obj_selected_idx];
	if (obj.type == TYPE_SPHERE)
		move_sphere(obj.data, dx, dy, dz);
	if (obj.type == TYPE_PLANE)
		move_plane(obj.data, dx, dy, dz);
	if (obj.type == TYPE_TRIANGLE)
		move_triangle(obj.data, dx, dy, dz);
	if (obj.type == TYPE_SQUARE)
		move_square(obj.data, dx, dy, dz);
	if (obj.type == TYPE_CYLINDER)
		move_cylinder(obj.data, dx, dy, dz);
}

void	resize_object(t_mlx *rt, double amount)
{
	t_objects	obj;

	obj = rt->objects_array[rt->obj_selected_idx];
	if (obj.type == TYPE_SPHERE)
		resize_sphere(obj.data, amount);
	if (obj.type == TYPE_SQUARE)
		resize_square(obj.data, amount);
	if (obj.type == TYPE_CYLINDER)
		resize_cylinder(obj.data, amount);
}

void	rotate_object(t_mlx *rt, double dx, double dy)
{
	t_objects	obj;

	obj = rt->objects_array[rt->obj_selected_idx];
	if (obj.type == TYPE_PLANE)
		rotate_plane(obj.data, dx, dy);
	if (obj.type == TYPE_SQUARE)
		rotate_square(obj.data, dx, dy);
	if (obj.type == TYPE_CYLINDER)
		rotate_cylinder(obj.data, dx, dy);
}

void	show_object_info(int idx, t_mlx *rt)
{
	t_cam	*cam;
	char	*msg[3];
	int		i;
	char	*idxstring;

	idxstring = ft_itoa(idx);
	msg[0] = ft_strjoin("object selected idx:", idxstring);
	msg[1] = g_obj_type_string[rt->objects_array[idx].type];
	msg[2] = NULL;
	cam = rt->cam_list->content;
	mlx_put_image_to_window(rt->mlx, rt->win, cam->image.img_ptr, 0, 0);
	i = -1;
	while (msg[++i] != NULL)
	{
		mlx_string_put(rt->mlx, rt->win, 11, 20 * i + 21, 0, msg[i]);
		mlx_string_put(rt->mlx, rt->win, 10, 20 * i + 20,
			255 << 16 | 255 << 8 | 255, msg[i]);
	}
	free(idxstring);
	free(msg[0]);
}
