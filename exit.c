/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 15:25:55 by kanlee            #+#    #+#             */
/*   Updated: 2020/12/10 15:19:02 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft/libft.h"

int		close_window(t_mlx *param)
{
	int i;

	if (param->win)
		mlx_destroy_window(param->mlx, param->win);
	i = -1;
	while (++i < param->objs_cnt)
		free(param->objects_array[i].data);
	ft_lstclear(&(param->lights_list), free);
	ft_lstclear(&(param->cam_list), free);
	exit(0);
}

void	exit_error(char *str, t_mlx *rt)
{
	ft_putstr_fd("Error\n", 1);
	ft_putstr_fd(str, 1);
	close_window(rt);
	return ;
}
