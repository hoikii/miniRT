#ifndef KEY_H
# define KEY_H

# include "minirt.h"

# ifdef LINUX
#  define KEYPRESS 2
#  define KEYPRESSMASK 1L<<0
#  define DESTROYNOTIFY 17
#  define STRUCTURENOTIFYMASK 1L<<17
#  define KEY_ESC 65307
#  define KEY_A 97
#  define KEY_S 115
#  define KEY_D 100
#  define KEY_W 119
#  define KEY_LEFT 65361
#  define KEY_RIGHT 65363
#  define KEY_DOWN 65364
#  define KEY_UP 65362
#  define KEY_PLUS 65451
#  define KEY_MINUS 65453
# else
#  define KEYPRESS 2
#  define KEYPRESSMASK 1
#  define DESTROYNOTIFY 17
#  define STRUCTURENOTIFYMASK 1L<<17
#  define KEY_ESC 53
#  define KEY_A 0
#  define KEY_S 1
#  define KEY_D 2
#  define KEY_W 13
#  define KEY_LEFT 123
#  define KEY_RIGHT 124
#  define KEY_DOWN 125
#  define KEY_UP 126
#  define KEY_PLUS 69
#  define KEY_MINUS 78
# endif

int key_pressed(int keycode, t_mlx *param);


#endif
