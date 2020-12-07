/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 13:17:23 by kanlee            #+#    #+#             */
/*   Updated: 2020/12/07 14:45:17 by kanlee           ###   ########.fr       */
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

typedef struct s_img {
	void * img;
	int bpp;
	int size_line;
	int endian;
} t_img;

typedef struct s_ambient {
	double brightness;
	t_color color;
} t_ambient;

typedef struct s_rec {
	t_color color;
	double t;
	t_vec normal;
	t_vec point;
} t_rec;

typedef enum e_obj_type {
	TYPE_SPHERE = 0,
	TYPE_PLANE,
	TYPE_TRIANGLE
} t_obj_type;

typedef struct s_objects {
	t_obj_type type;
	void *data;
} t_objects;


typedef struct s_mlx {
	void *mlx;
	void *win;
	void *img;
	char *imgdata;
	int bpp;
	int size_line;
	int endian;
	int screen_height;
	int screen_width;
	t_cam cam;
	t_list *cam_list_head;
	t_list *cam_list;
	t_ambient ambient;
	t_list *lights;
	int objs_cnt;
	t_objects *objects_array;
} t_mlx;

int close_window(t_mlx *param);
void draw(t_mlx *);
#endif
