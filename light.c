/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 14:44:24 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/30 19:07:35 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "light.h"
#include "objects.h"
#include "math_utils.h"
#include "disruption.h"
#include "uv_mapping.h"

t_light	*new_light(t_vec position, double brightness, t_color color)
{
	t_light	*l;

	l = malloc(sizeof(t_light));
	if (!l)
		return (NULL);
	l->position = position;
	l->brightness = brightness;
	l->color = color;
	return (l);
}

int		is_shadow(t_vec op, t_vec lightdir, t_mlx *rt, t_light *light)
{
	t_ray	tolight;
	int		i;
	t_rec	tmp;
	double	distance;

	tolight.origin = op;
	tolight.direction = lightdir;
	distance = v_len(v_sub(light->position, op));
	i = -1;
	while (++i < rt->objs_cnt)
	{
		if (hit(rt->objects_array[i], tolight, distance, &tmp))
			return (1);
	}
	return (0);
}

t_color	calc_specular(t_rec rec, t_vec lightdir, double diff, t_light *light)
{
	double	spec;
	t_vec	reflect;

	if (diff <= 0)
		return (color(0, 0, 0));
	reflect = v_unit(v_sub(v_mul(rec.normal, 2 * diff), lightdir));
	spec = clamp(v_dot(reflect, v_mul(rec.raydir, -1)), -1, 1);
	if (spec > 0)
		return (c_mul(light->color, pow(spec, 10) * 0.5 * light->brightness));
	return (color(0, 0, 0));
}

t_color	apply_light(t_rec rec, int idx, t_mlx *rt)
{
	t_light	light;
	t_vec	lightdir;
	t_color	result;
	t_color	specular;
	double	diff;

	specular = color(0, 0, 0);
	result = c_mul(rt->ambient.color, rt->ambient.brightness);
	idx = -1;
	while (++idx < rt->lights_cnt)
	{
		light = rt->lights_array[idx];
		lightdir = v_unit(v_sub(light.position, rec.point));
		if (is_shadow(rec.point, lightdir, rt, &light))
			continue ;
		diff = clamp(v_dot(rec.normal, lightdir), 0, 1);
		result = c_add(result, c_mul(light.color, diff * light.brightness));
		specular = c_add(specular, calc_specular(rec, lightdir, diff, &light));
	}
	if (BONUS && rec.bonus.texture_type == TEXTURE_RAINBOW)
		return (c_add(c_mix(rainbow(rec), result), specular));
	if (BONUS && rec.bonus.texture_type == TEXTURE_CHECKERBOARD)
		return (c_add(c_mix(checkerboard(rec, rt), result), specular));
	if (BONUS && rec.bonus.texture_type == TEXTURE_UVMAP)
		return (c_add(c_mix(uvmap(rec, rt), result), specular));
	return (c_add(c_mix(rec.color, result), specular));
}

void	move_light(t_mlx *rt, t_vec mv)
{
	t_light	*light;

	light = &(rt->lights_array[rt->light_sel_idx]);
	light->position = v_add(light->position, mv);
}
