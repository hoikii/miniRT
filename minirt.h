/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 13:17:23 by kanlee            #+#    #+#             */
/*   Updated: 2020/12/13 17:19:12 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include "minilibx/mlx.h"
# include "vec.h"
# include "camera.h"
# include "color.h"
# include "libft/libft.h"

# define PI 3.141592653897932385
# define EPSILON 0.0001

# define THREADS_CNT 3

typedef struct	s_img {
	void		*img;
	int			bpp;
	int			size_line;
	int			endian;
}				t_img;

typedef struct	s_ambient {
	double		brightness;
	t_color		color;
}				t_ambient;

typedef struct	s_rec {
	t_color		color;
	double		t;
	t_vec		normal;
	t_vec		point;
	t_vec		raydir;
}				t_rec;

typedef enum	e_obj_type {
	TYPE_SPHERE = 0,
	TYPE_PLANE,
	TYPE_TRIANGLE
}				t_obj_type;

typedef struct	s_objects {
	t_obj_type	type;
	void		*data;
}				t_objects;

typedef struct	s_mlx {
	void		*mlx;
	void		*win;
	void		*img;
	char		*imgdata;
	int			bpp;
	int			size_line;
	int			endian;
	int			screen_height;
	int			screen_width;
	int			resolution_declared;
	t_ambient	ambient;
	int			ambient_declared;
	t_cam		cam;
	t_list		*cam_list;
	t_list		*lights_list;
	int			objs_cnt;
	t_objects	*objects_array;
}				t_mlx;

typedef struct	s_thread {
	t_mlx		*mlx;
	int			tid;
}				t_thread;

void			draw(t_mlx *rt);

#endif
