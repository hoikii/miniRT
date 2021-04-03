/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 21:29:59 by kanlee            #+#    #+#             */
/*   Updated: 2021/04/04 01:46:51 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "objects.h"
#include "hit.h"
#include "math_utils.h"

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
	if (obj.type == TYPE_CYLINDER_CAPS)
		return (hit_cylinder_caps(obj.data, ray, tmax, rec));
	if (obj.type == TYPE_CUBE)
		return (hit_cube(obj.data, ray, tmax, rec));
	if (obj.type == TYPE_PYRAMID)
		return (hit_pyramid(obj.data, ray, tmax, rec));
	return (0);
}

void	move_object(t_mlx *rt, t_vec mv)
{
	t_objects	obj;

	obj = rt->objects_array[rt->obj_selected_idx];
	if (obj.type == TYPE_SPHERE)
		move_sphere(obj.data, mv);
	if (obj.type == TYPE_PLANE)
		move_plane(obj.data, mv);
	if (obj.type == TYPE_TRIANGLE)
		move_triangle(obj.data, mv);
	if (obj.type == TYPE_SQUARE)
		move_square(obj.data, mv);
	if (obj.type == TYPE_CYLINDER || obj.type == TYPE_CYLINDER_CAPS)
		move_cylinder(obj.data, mv);
	if (obj.type == TYPE_CUBE)
		move_cube(obj.data, mv);
	if (obj.type == TYPE_PYRAMID)
		move_pyramid(obj.data, mv);
}

void	resize_object(t_mlx *rt, double amount, int flag)
{
	t_objects	obj;

	obj = rt->objects_array[rt->obj_selected_idx];
	if (obj.type == TYPE_SPHERE)
		resize_sphere(obj.data, amount);
	if (obj.type == TYPE_SQUARE)
		resize_square(obj.data, amount);
	if (obj.type == TYPE_CYLINDER || obj.type == TYPE_CYLINDER_CAPS)
		resize_cylinder(obj.data, amount, flag);
	if (obj.type == TYPE_CUBE)
		resize_cube(obj.data, amount);
	if (obj.type == TYPE_PYRAMID)
		resize_pyramid(obj.data, amount, flag);
}

void	rotate_object(t_mlx *rt, t_vec axis, double angle)
{
	t_objects	obj;

	obj = rt->objects_array[rt->obj_selected_idx];
	if (obj.type == TYPE_PLANE)
		rotate_plane(obj.data, axis, angle);
	if (obj.type == TYPE_SQUARE)
		rotate_square(obj.data, axis, angle);
	if (obj.type == TYPE_CYLINDER || obj.type == TYPE_CYLINDER_CAPS)
		rotate_cylinder(obj.data, axis, angle);
	if (obj.type == TYPE_CUBE)
		rotate_cube(obj.data, axis, angle);
	if (obj.type == TYPE_PYRAMID)
		rotate_pyramid(obj.data, axis, angle);
}

int		modify_wave_attr(t_mlx *rt, int is_brace, int incdec)
{
	t_objects		obj;
	t_bonus_attr	*bonus;

	obj = rt->objects_array[rt->obj_selected_idx];
	if (obj.type == TYPE_SPHERE)
		bonus = &((t_sphere *)(obj.data))->bonus;
	if (obj.type == TYPE_PLANE)
		bonus = &((t_plane *)(obj.data))->bonus;
	if (obj.type == TYPE_TRIANGLE)
		bonus = &((t_triangle *)(obj.data))->bonus;
	if (obj.type == TYPE_SQUARE)
		bonus = &((t_square *)(obj.data))->bonus;
	if (obj.type == TYPE_CYLINDER)
		bonus = &((t_cylinder *)(obj.data))->bonus;
	if (bonus->texture_type != TEXTURE_WAVE)
		return (0);
	if (is_brace)
		bonus->wave_frequency += 5 * incdec;
	else
		bonus->wave_amplitude += 0.01 * incdec;
	bonus->wave_frequency = clamp(bonus->wave_frequency, 0, 200);
	bonus->wave_amplitude = clamp(bonus->wave_amplitude, 0, 0.2);
	return (1);
}
