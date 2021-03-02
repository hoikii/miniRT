/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 16:18:16 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/02 19:03:18 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_utils.h"
#include "exit.h"

void	skip_blank(char **line)
{
	while (**line && **line == ' ')
		(*line)++;
	return ;
}

void	append_object(void *obj, int type, t_mlx *rt)
{
	t_objects	new_item;
	t_objects	*newarray;
	int			cnt;
	int			i;

	new_item.type = type;
	new_item.data = obj;
	cnt = rt->objs_cnt;
	if ((cnt + 1) % 10 == 1)
	{
		if (!(newarray = malloc((sizeof(t_objects) * (cnt + 10)))))
			exit_error("Memory allocation failed.", rt);
		i = -1;
		while (++i < cnt)
			newarray[i] = rt->objects_array[i];
		if (cnt > 0)
			free(rt->objects_array);
		newarray[i] = new_item;
		rt->objects_array = newarray;
	}
	else
		rt->objects_array[cnt] = new_item;
	(rt->objs_cnt)++;
	return ;
}

void	free_words(char **words)
{
	int i;

	i = 0;
	while (words[i])
	{
		free(words[i]);
		i++;
	}
	free(words);
	return ;
}
