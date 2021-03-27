/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 15:25:55 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/27 19:08:54 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft/libft.h"
#include "camera.h"

static void	destroy_img(t_mlx *rt)
{
	t_list	*tmp;
	t_list	*head;
	t_cam	*cam;

	head = rt->cam_list;
	tmp = head;
	while (tmp)
	{
		cam = tmp->content;
		if (cam->image.img_ptr != NULL)
			mlx_destroy_image(rt->mlx, cam->image.img_ptr);
		tmp = tmp->next;
		if (tmp == head)
			break ;
	}
}

int			close_window(t_mlx *param)
{
	int	i;

	if (param->win)
		mlx_destroy_window(param->mlx, param->win);
	i = -1;
	while (++i < param->objs_cnt)
		free(param->objects_array[i].data);
	ft_lstclear(&(param->lights_list), free);
	destroy_img(param);
	ft_lstclear(&(param->cam_list), free);
	exit(0);
}

void		exit_error(char *str, t_mlx *rt)
{
	printf("Error\n");
	printf("%s\n", str);
	close_window(rt);
	return ;
}

void		exit_error_ln(char *str, t_mlx *rt, int linenumber)
{
	printf("Error\n");
	printf("line #%d: %s\n", linenumber, str);
	close_window(rt);
	return ;
}
