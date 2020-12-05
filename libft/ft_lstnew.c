/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 18:30:36 by kanlee            #+#    #+#             */
/*   Updated: 2020/11/27 14:18:55 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list	*ft_lstnew(void *content, int type)
{
	t_list *node;

	if (!(node = (t_list *)(malloc(sizeof(t_list)))))
		return (NULL);
	node->content = content;
	node->type = type;
	node->next = (NULL);
	return (node);
}
