/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 23:37:08 by kanlee            #+#    #+#             */
/*   Updated: 2020/10/10 02:43:48 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	size_t	i;
	char	*dst;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (!(dst = malloc(sizeof(char) * (len1 + len2 + 1))))
		return (NULL);
	i = 0;
	ft_memcpy(dst, s1, len1);
	ft_memcpy(dst + len1, s2, len2);
	dst[len1 + len2] = '\0';
	return (dst);
}
