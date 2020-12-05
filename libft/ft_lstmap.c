/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 14:06:18 by kanlee            #+#    #+#             */
/*   Updated: 2020/11/27 14:23:03 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list *new_first;
	t_list *tmp;
	t_list *prev;

	if (!lst || !f)
		return (NULL);
	if (!(new_first = ft_lstnew((*f)(lst->content), 0)))
		return (NULL);
	prev = new_first;
	tmp = lst->next;
	while (tmp)
	{
		if (!(prev->next = ft_lstnew((*f)(tmp->content), 0)))
		{
			ft_lstclear(&new_first, del);
			return (NULL);
		}
		prev = prev->next;
		tmp = tmp->next;
	}
	return (new_first);
}
