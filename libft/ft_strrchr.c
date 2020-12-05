/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 14:15:41 by kanlee            #+#    #+#             */
/*   Updated: 2020/10/04 16:52:16 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	size_t	last_idx;
	int		found;

	found = 0;
	i = 0;
	while (1)
	{
		if (s[i] == c)
		{
			found = 1;
			last_idx = i;
		}
		if (s[i] == 0)
			break ;
		i++;
	}
	return ((found) ? ((char *)s + last_idx) : 0);
}
