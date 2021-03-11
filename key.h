/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 10:07:51 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/11 16:39:39 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEY_H
# define KEY_H

# include "minirt.h"

# ifdef LINUX
#  define KEYPRESS 2
#  define KEYPRESSMASK 1L<<0
#  define CLIENTMESSAGE 33
#  define WM_DELETE_WINDOW 3
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
#  define KEY_SPACE 32
#  define KEY_O 111
#  define KEY_C 99
#  define KEY_Q -1
#  define KEY_Z -1
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
#  define KEY_SPACE 49
#  define KEY_O 31
#  define KEY_C 8
#  define KEY_Q 12
#  define KEY_Z 6
# endif

int	key_pressed(int keycode, t_mlx *param);

#endif
