/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 13:17:23 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/05 22:23:42 by kanlee           ###   ########.fr       */
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

# define STDOUT 1

# define PI 3.141592653897932385
# define EPSILON 0.0001

# define MIN_X 20
# define MIN_Y 20

# ifndef BONUS
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
	TYPE_TRIANGLE,
	TYPE_SQUARE,
	TYPE_CYLINDER
}				t_obj_type;

typedef struct	s_objects {
	t_obj_type	type;
	void		*data;
}				t_objects;

typedef struct	s_mlx {
	void		*mlx;
	void		*win;
	int			bpp;
	int			size_line;
	int			endian;
	int			screen_height;
	int			screen_width;
	int			resolution_declared;
	t_ambient	ambient;
	int			ambient_declared;
	t_list		*cam_list;
	t_list		*lights_list;
	int			objs_cnt;
	t_objects	*objects_array;
}				t_mlx;

typedef struct	s_thread {
	t_mlx		*mlx;
	int			tid;
}				t_thread;

int				g_threads_progress[THREADS_CNT];
void			render_scene(t_mlx *rt, int save_bmp);

#endif
