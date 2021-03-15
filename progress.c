/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   progress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 01:05:03 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/15 14:34:29 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Use write() instead of printf() because flusing buffer is needed but
** fflush() or setbuf() isn't allowed.
*/

#include "minirt.h"
#include "libft/libft.h"

int		g_threads_progress[THREADS_CNT + 1];

void	print_progress(int tid, int current)
{
	int	i;

	if (tid == -1)
	{
		ft_putstr_fd("\rrenndering ", STDOUT);
		ft_putnbr_fd(current, STDOUT);
		ft_putchar_fd('%', STDOUT);
		return ;
	}
	if (g_threads_progress[THREADS_CNT] == 1)
		return ;
	g_threads_progress[THREADS_CNT] = 1;
	ft_putchar_fd('\r', STDOUT);
	g_threads_progress[tid] = current;
	i = -1;
	while (++i < THREADS_CNT)
	{
		ft_putchar_fd('t', STDOUT);
		ft_putnbr_fd(i, STDOUT);
		ft_putstr_fd(": ", STDOUT);
		ft_putnbr_fd(g_threads_progress[i], STDOUT);
		ft_putstr_fd("%   ", STDOUT);
	}
	g_threads_progress[THREADS_CNT] = 0;
}