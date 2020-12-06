/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 16:18:16 by kanlee            #+#    #+#             */
/*   Updated: 2020/12/05 18:18:13 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_utils.h"

void skip_blank(char **line)
{
	while (**line && **line == ' ')
		(*line)++;
	return ;
}

void skip_sep(char **line)
{
	skip_blank(line);
	while (**line && **line == ',')
		(*line)++;
	skip_blank(line);
	return ;
}

void append_object(void *obj, int type, t_mlx *rt)
{
	int cnt;
	int i;
	t_objects new_item;

	new_item.type = type;
	new_item.data = obj;
	cnt = rt->objs_cnt;
	if ((cnt + 1) % 10 == 1)
	{
		t_objects *newarray = malloc((sizeof(t_objects) * (cnt + 10)));
		for (i = 0; i < cnt; i++)
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
