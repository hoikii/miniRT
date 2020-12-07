/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 14:44:24 by kanlee            #+#    #+#             */
/*   Updated: 2020/12/08 02:07:49 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "light.h"
#include "objects.h"

t_light *new_light(t_vec position, double brightness, t_color color)

{
	t_light *l = malloc(sizeof(t_light));
	l->position = position;
	l->brightness = brightness;
	l->color = color;
	return l;
}

void free_light(t_light *light)
{
	free(light);
	return ;
}

t_color	compute_light(t_ray ray, t_rec rec, t_mlx *rt)
{
	t_list *light = rt->lights;
	t_color amb = c_mul(rt->ambient.color, rt->ambient.brightness);
	t_vec op = rec.point;

	t_color diffuse_sum = color(0,0,0);
	t_color specular_sum = color(0,0,0);
	while (light != NULL) {
		t_vec lightdir = v_unit(v_sub(((t_light *)(light->content))->position, rec.point));
		double diff = v_dot(rec.normal, lightdir);
		if (diff < 0)
			diff = 0;
		t_color diffuse = c_mul(((t_light *)(light->content))->color, diff);

		t_vec reflect = v_unit(v_sub(v_mul(rec.normal, 2 * diff), lightdir));
		double cosa = v_dot(reflect, v_mul(ray.direction, -1));
		t_color specular;
		if (cosa >= 1)
			cosa = 1;
		if (cosa <= 0 || diff <= 0)
			specular = color(0,0,0);
		else
			specular = c_mul(((t_light *)(light->content))->color, pow(cosa, 100));
specular = color(0,0,0);

		t_ray tolight;
		tolight.origin = op;
		tolight.direction = lightdir;
		double distance = v_len(v_sub(((t_light *)(light->content))->position, op)) / v_len(lightdir);
		t_rec tmp;

		for (int i = 0; i < rt->objs_cnt; i++)
		{
			if (hit(rt->objects_array[i], tolight, distance, &tmp))
			{
					specular = color(0,0,0);
					diffuse = color(0,0,0);
					break;
			}
		}

		diffuse_sum = c_add(diffuse_sum, diffuse);
		specular_sum = c_add(specular_sum, specular);
		light = light->next;
	}
	return c_add(c_add(amb, diffuse_sum), specular_sum);
}
