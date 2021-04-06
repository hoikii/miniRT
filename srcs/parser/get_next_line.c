/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 18:05:53 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/13 02:52:01 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"
#include "../libft/libft.h"

static void	set_line(char **line, t_prev_info *stored, char *buf, char *nl)
{
	size_t	size;

	size = (size_t)(nl - buf);
	*line = malloc(sizeof(char) * (stored->len + size + 1));
	if (*line)
	{
		ft_memcpy(*line, stored->str, stored->len);
		ft_memcpy(*line + stored->len, buf, size);
		(*line)[stored->len + size] = '\0';
	}
}

static int	stored_has_newline(t_prev_info *stored, char **line)
{
	char	*nl;
	size_t	size;

	nl = ft_memchr(stored->str, '\n', stored->len);
	if (!nl)
		return (0);
	size = (size_t)(nl - stored->str);
	*line = malloc(sizeof(char) * (size + 1));
	if (*line)
	{
		ft_memcpy(*line, stored->str, size);
		(*line)[size] = '\0';
	}
	stored->str = append(stored->str, nl + 1, 0, stored->len - size - 1);
	stored->len = stored->len - size - 1;
	return (1);
}

static int	buf_has_newline(char *buf, ssize_t bytes_read, t_prev_info *stored,
		char **line)
{
	char	*nl;
	size_t	size;

	nl = ft_memchr(buf, '\n', bytes_read);
	if (!nl)
	{
		stored->str = append(stored->str, buf, stored->len, bytes_read);
		stored->len += bytes_read;
		return (0);
	}
	set_line(line, stored, buf, nl);
	size = (size_t)(nl - buf + 1);
	stored->str = append(stored->str, buf + size, 0, bytes_read - size);
	stored->len = bytes_read - size;
	return (1);
}

static void	init_value(t_prev_info *stored)
{
	if (stored->str == NULL)
	{
		stored->str = ft_strdup("");
		stored->len = 0;
	}
}

int			get_next_line(int fd, char **line)
{
	static t_prev_info	stored;
	char				*buf;
	ssize_t				bytes_read;

	if (fd < 0 || !line || BUFFER_SIZE <= 0 || fd >= 1024)
		return (-1);
	init_value(&stored);
	if (stored_has_newline(&stored, line))
		return (1);
	buf = malloc(sizeof(char) * BUFFER_SIZE);
	if (!buf)
		return (-1);
	while (1)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		if (buf_has_newline(buf, bytes_read, &stored, line))
			return (set_ret_value(buf, bytes_read));
	}
	*line = append(stored.str, "", stored.len, 1);
	stored.str = NULL;
	if (bytes_read < 0)
		*line = 0;
	return (set_ret_value(buf, bytes_read));
}
