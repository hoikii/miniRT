/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 19:19:29 by kanlee            #+#    #+#             */
/*   Updated: 2020/10/10 01:43:35 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*ptr;

	len = 0;
	while (s[len++])
		;
	if (!(ptr = malloc(sizeof(char) * len)))
		return (NULL);
	while (len--)
		ptr[len] = s[len];
	return (ptr);
}
