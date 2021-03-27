/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 13:17:23 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/27 19:19:11 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include "minilibx/mlx.h"
# include "vec.h"
# include "color.h"
# include "light_def.h"
# include "libft/libft.h"

# define STDOUT 1

# define PI 3.141592653897932385
# define EPSILON 0.0001

# define MIN_X 20
# define MIN_Y 20

# define MV_INC 0.2
# define MV_DEC -0.2
# define ROTATE_INC 10
# define ROTATE_DEC -10

# ifdef BONUS
#  undef BONUS
#  define BONUS 1
# else
#  define BONUS 0
# endif

# ifndef THREADS_CNT
#  define THREADS_CNT 1
# endif

# ifndef REFLECTION_DEPTH
#  define REFLECTION_DEPTH 3
# endif

/*
** Since standard library macros aren't allowed by norminette,
** define uint32_t manually.
** This may not be necessary because most system/compiler uses 4 bytes for int
** and 2 bytes for short.
*/

typedef int		t_uint32_t;
typedef short	t_uint16_t;

/*
** Define DBL_MAX manually instead of using float.h
*/
# define DBL_MAX 1.79769e+308

typedef struct	s_img {
	void		*img_ptr;
	char		*imgdata;
	int			width;
	int			height;
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
	int			obj_id;
	int			objtype;
	int			bonus;
}				t_rec;

typedef enum	e_obj_type {
	TYPE_SPHERE = 0,
	TYPE_PLANE,
	TYPE_TRIANGLE,
	TYPE_SQUARE,
	TYPE_CYLINDER,
	TYPE_CYLINDER_CAPS,
	TYPE_CUBE,
	TYPE_PYRAMID
}				t_obj_type;

typedef struct	s_objects {
	t_obj_type	type;
	void		*data;
}				t_objects;

typedef enum	e_transform_mode {
	MODE_CAM = 0,
	MODE_OBJ,
	MODE_LIGHT
}				t_transform_mode;

typedef enum	e_color_filter {
	FILTER_NONE = 0,
	FILTER_RED,
	FILTER_GREEN,
	FILTER_BLUE,
	FILTER_GREY,
	FILTER_SEPIA,
	FILTER_SEPIA2,
	FILTER_INVERSE
}				t_color_filter;

# define FILTER_CNT 8

typedef enum	e_texture {
	TEXTURE_NONE = 0,
	TEXTURE_RAINBOW,
	TEXTURE_CHECKERBOARD,
	TEXTURE_WAVE,
	TEXTURE_UVMAP
}				t_texture;



typedef struct	s_mlx {
	void		*mlx;
	void		*win;
	int			screen_height;
	int			screen_width;
	int			resolution_declared;
	t_ambient	ambient;
	int			ambient_declared;
	t_list		*cam_list;
	t_list		*lights_list;
	t_light		*lights_array;
	int			lights_cnt;
	int			objs_cnt;
	t_objects	*objects_array;
	int			transform_mode;
	int			obj_selected_idx;
	int			light_sel_idx;
	int			color_filter;

	int anti_aliasing;
#if 0
	double frequency;
	double amplitude;
#endif
}				t_mlx;

typedef struct	s_thread {
	t_mlx		*mlx;
	int			tid;
}				t_thread;

void			render_scene(t_mlx *rt, int save_bmp);
int				put_img_to_window(t_mlx *rt);

#endif
