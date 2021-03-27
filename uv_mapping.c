/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_mapping.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 14:44:24 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/28 04:31:44 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "uv_mapping.h"
#include "objects.h"
#include "color.h"
#include "math_utils.h"

static void		get_spherical_coords(t_vec pos, double *u, double *v)
{
	double	theta;
	double	phi;

	theta = acos(pos.y);
	phi = atan2(pos.z, pos.x) + PI;
	*u = phi / (2 * PI);
	*v = theta / PI;
	*u = clamp(*u, 0, 1);
	*v = clamp(*v, 0, 1);
	return ;
}

static t_color	get_texture_color(t_img texture, double u, double v)
{
	t_color			ret;
	unsigned int	color;
	int				x;
	int				y;
	int				pos;

	x = u * (texture.width - 1);
	y = v * (texture.height - 1);
	pos = y * texture.size_line + x * texture.bpp / 8;
	color = *(unsigned int *)(&texture.imgdata[pos]);
	ret.r = color << 8 >> 24;
	ret.g = color << 16 >> 24;
	ret.b = color << 24 >> 24;
	ret = c_mul(ret, 1.0 / 255);
	return (ret);
}

t_color			uvmap(t_rec rec, t_mlx *rt)
{
	t_sphere	*sp;
	double		u;
	double		v;

	sp = (t_sphere *)rt->objects_array[rec.obj_id].data;
	get_spherical_coords(rec.normal, &u, &v);
	return (get_texture_color(sp->texture, u, v));
}
