#ifndef KEY_H
# define KEY_H

# include "minirt.h"

# define X_EVENT_KEY_EXIT 17
# define X_EVENT_KEY_PRESS 2
# define KEY_ESC 53
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_W 13
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_DOWN 125
# define KEY_UP 126
# define KEY_PLUS 69
# define KEY_MINUS 78

int key_pressed(int keycode, t_mlx *param);


#endif
