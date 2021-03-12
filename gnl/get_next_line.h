/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 18:02:48 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/13 02:36:13 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# define BUFFER_SIZE 100

typedef struct	s_prev_info
{
	char		*str;
	size_t		len;
	int			reached;
}				t_prev_info;

int				get_next_line(int fd, char **line);
char			*append(char *s1, char *s2, int len1, int len2);
int				set_ret_value(char *buf, ssize_t bytes_read);
#endif
