/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 18:07:50 by kanlee            #+#    #+#             */
/*   Updated: 2020/12/03 12:17:40 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "get_next_line.h"

char	*append(char *s1, char *s2, int len1, int len2)
{
	char *tmp;

	if (!(tmp = malloc(sizeof(char) * (len1 + len2))))
		return (0);
	ft_memcpy(tmp, s1, len1);
	ft_memcpy(tmp + len1, s2, len2);
	free(s1);
	s1 = tmp;
	return (tmp);
}
