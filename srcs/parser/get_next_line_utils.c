/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 18:07:50 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/13 02:38:54 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "get_next_line.h"

char	*append(char *s1, char *s2, int len1, int len2)
{
	char	*tmp;

	tmp = malloc(sizeof(char) * (len1 + len2));
	if (!tmp)
		return (0);
	ft_memcpy(tmp, s1, len1);
	ft_memcpy(tmp + len1, s2, len2);
	free(s1);
	s1 = tmp;
	return (tmp);
}

int		set_ret_value(char *buf, ssize_t bytes_read)
{
	free(buf);
	if (bytes_read > 0)
		return (1);
	else
		return (bytes_read);
}
